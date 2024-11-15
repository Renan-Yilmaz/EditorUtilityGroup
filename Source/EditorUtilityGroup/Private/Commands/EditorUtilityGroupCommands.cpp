#include "Commands/EditorUtilityGroupCommands.h"
#include "Settings/UEditorUtilityGroupSettings.h"

#define LOCTEXT_NAMESPACE "EditorUtilityGroupCommands"

void FEditorUtilityGroupCommands::RegisterCommands()
{
		UI_COMMAND(OpenWidget, "Open Widget", "Open Widget", EUserInterfaceActionType::Button, FInputChord());
}