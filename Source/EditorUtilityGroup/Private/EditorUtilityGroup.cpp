// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorUtilityGroup.h"

#include "EditorAssetLibrary.h"
#include "ToolMenus.h"
#include "ToolMenuSection.h"
#include "Commands/EditorUtilityGroupCommands.h"
#include "EditorUtilityWidget.h"
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "IAssetViewport.h"
#include "LevelEditor.h"
#include "LevelEditorActions.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "Editor/UnrealEdEngine.h"
#include "Settings/UEditorUtilityGroupSettings.h"
#include "Style/EditorUtilityGroupStyle.h"
#include "Developer/Settings/Private/SettingsContainer.h"

#define LOCTEXT_NAMESPACE "FEditorUtilityGroupModule"

void FEditorUtilityGroupModule::StartupModule()
{
	FEditorUtilityGroupStyle::Initialize();
	FEditorUtilityGroupStyle::ReloadTextures();
	FEditorUtilityGroupCommands::Register();


	BindCommands();
	BuildMenu();
	IModuleInterface::StartupModule();
}

void FEditorUtilityGroupModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FEditorUtilityGroupModule::BuildMenu()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");
		SettingsContainer->DescribeCategory("Editor Widget Group Plugin",
		                                    LOCTEXT("RuntimeWDCategoryName", "Editor Widget Group  Plugin"),
		                                    LOCTEXT("RuntimeWDCategoryDescription",
		                                            "Editor Widget Group  configuration"));

		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings(
			"Project", "Editor Widget Group  Plugin", "Editor Widget Group  Configuration",
			LOCTEXT("RuntimeGeneralSettingsName", "Editor Widget Group  Configuration"),
			LOCTEXT("RuntimeGeneralSettingsDescription", "Base configuration for Editor Widget Group"),
			GetMutableDefault<UEditorUtilityGroupSettings>()
		);

		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this, &FEditorUtilityGroupModule::SettingsChanged);
		}
	}

	UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
	{
		FToolMenuSection& MenuSection = ToolbarMenu->FindOrAddSection("PluginTools");
		{
			FToolMenuSection& PlaySection = ToolbarMenu->FindOrAddSection("Play");
			FUIAction SelectModeMenu;

			FToolMenuEntry NewEntry = FToolMenuEntry::InitComboButton("List Tool", SelectModeMenu,
			                                                          FOnGetContent::CreateLambda([this]
			                                                          {
				                                                          return CreateSubMenu();
			                                                          }),LOCTEXT("List Tool", "List Tool"),
			                                                          LOCTEXT("Select Tool",
			                                                                  "Open your tool"),
			                                                          FSlateIcon(
				                                                          FEditorUtilityGroupStyle::Get().
				                                                          GetStyleSetName(),
				                                                          "EditorUtilityGroup.OpenWidget"), false,
			                                                          "Select tool");
			NewEntry.StyleNameOverride = "CalloutToolbar";
			PlaySection.AddEntry(NewEntry);
		}
	}
}

bool FEditorUtilityGroupModule::SettingsChanged()
{
	RebuildListWidget();
	return true;
}

void FEditorUtilityGroupModule::RebuildListWidget()
{
	static const FName MenuName("UnrealEd.PlayWorldCommands.ListTool");
	if (UToolMenus::Get()->IsMenuRegistered(MenuName))
	{
		UToolMenu* Menu = UToolMenus::Get()->RegisterMenu(MenuName);
		Menu->RemoveSection("ListTool");
		FToolMenuSection& EnvironmentOptionsSection = Menu->AddSection("ListTool",
		                                                               LOCTEXT("ListTool",
		                                                                       "ListTool"));
		const UEditorUtilityGroupSettings* Settings = GetDefault<UEditorUtilityGroupSettings>();
		for (FString WidgetPath : Settings->ListWidgetPath)
		{
			UObject* Blueprint = UEditorAssetLibrary::LoadAsset(WidgetPath);
			if (IsValid(Blueprint))
			{
				EnvironmentOptionsSection.AddMenuEntry(
					FName(*WidgetPath),
					FText::FromString(Blueprint->GetName()),
					FText::FromString("Open " + Blueprint->GetName()),
					FSlateIcon(FEditorUtilityGroupStyle::Get().GetStyleSetName(), "EditorUtilityGroup.OpenWidget"),
					FUIAction(FExecuteAction::CreateLambda([Blueprint]()
					{
						UEditorUtilityWidgetBlueprint* EditorWidget = Cast<UEditorUtilityWidgetBlueprint>(Blueprint);
						if (EditorWidget)
						{
							UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<
								UEditorUtilitySubsystem>();
							if (EditorWidget)
							{
								EditorUtilitySubsystem->SpawnAndRegisterTab(EditorWidget);
							}
						}
					}))
				);
			}
		}
	}
}

void FEditorUtilityGroupModule::BindCommands()
{
	UICommandList = MakeShareable(new FUICommandList);
}

TSharedRef<SWidget> FEditorUtilityGroupModule::CreateSubMenu()
{
	const FEditorUtilityGroupCommands& Commands = FEditorUtilityGroupCommands::Get();
	static const FName MenuName("UnrealEd.PlayWorldCommands.ListTool");
	FToolMenuContext MenuContext(UICommandList);

	if (!UToolMenus::Get()->IsMenuRegistered(MenuName))
	{
		UToolMenu* Menu = UToolMenus::Get()->RegisterMenu(MenuName);
		FToolMenuSection& EnvironmentOptionsSection = Menu->AddSection("ListTool",
		                                                               LOCTEXT("ListTool",
		                                                                       "ListTool"));
		const UEditorUtilityGroupSettings* Settings = GetDefault<UEditorUtilityGroupSettings>();
		for (FString WidgetPath : Settings->ListWidgetPath)
		{
			UObject* Blueprint = UEditorAssetLibrary::LoadAsset(WidgetPath);
			if (IsValid(Blueprint))
			{
				EnvironmentOptionsSection.AddMenuEntry(
					FName(*WidgetPath),
					FText::FromString(Blueprint->GetName()),
					FText::FromString("Open " + Blueprint->GetName()),
					FSlateIcon(FEditorUtilityGroupStyle::Get().GetStyleSetName(), "EditorUtilityGroup.OpenWidget"),
					FUIAction(FExecuteAction::CreateLambda([Blueprint]()
					{
						UEditorUtilityWidgetBlueprint* EditorWidget = Cast<UEditorUtilityWidgetBlueprint>(Blueprint);
						if (EditorWidget)
						{
							UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<
								UEditorUtilitySubsystem>();
							EditorUtilitySubsystem->SpawnAndRegisterTab(EditorWidget);
						}
					}))
				);
			}
		}
	}
	return UToolMenus::Get()->GenerateWidget(MenuName, MenuContext);
}


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEditorUtilityGroupModule, EditorUtilityGroup)
