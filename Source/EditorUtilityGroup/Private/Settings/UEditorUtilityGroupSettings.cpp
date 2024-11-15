#include "Settings/UEditorUtilityGroupSettings.h"


UEditorUtilityGroupSettings::UEditorUtilityGroupSettings(const FObjectInitializer& ObjectInitializer)
{

}
#if WITH_EDITOR

void UEditorUtilityGroupSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
		// Try to Rebuild editor menu to handle change in settings but not seems to work
		// if (PropertyChangedEvent.Property == nullptr)
		// {
		// 	return;
		// }
		// IBHHEditorModule Editor = FModuleManager::Get().GetModuleChecked<IBHHEditorModule>("BigHelmetHeroesEditor");
		// Editor.BindCommands();
		// Editor.BuildMenu();
}

#endif	
