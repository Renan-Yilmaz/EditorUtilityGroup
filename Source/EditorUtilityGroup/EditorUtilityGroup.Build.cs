// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EditorUtilityGroup : ModuleRules
{
	public EditorUtilityGroup(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDefinitions.Add("EDITOR_UTILITY_GROUP_PLUGIN_CONFIG_FILE=\"DefaultEditorUtilityGroupPlugin.ini\"");
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"UnrealEd",
				"EditorStyle",
				"Blutility",
				"Engine",
				"EditorScriptingUtilities",
				"EditorWidgets",
				"DeveloperSettings",
				"UMG",
				"UMGEditor",
				"ToolMenus",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore", "EditorScriptingUtilities"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
