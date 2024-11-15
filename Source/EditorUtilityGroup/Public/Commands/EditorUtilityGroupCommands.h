#pragma once

#include "SlateBasics.h"
#include "Framework/Commands/Commands.h"
#include "Style/EditorUtilityGroupStyle.h"


class FEditorUtilityGroupCommands : public TCommands<FEditorUtilityGroupCommands>
{
public:
	FEditorUtilityGroupCommands(): TCommands<FEditorUtilityGroupCommands>
(
	TEXT("FEditorUtilityGroup"),
	NSLOCTEXT("Contexts", "FEditorUtilityGroup", "FEditorUtilityGroup"),
	NAME_None,
	FEditorUtilityGroupStyle::GetStyleSetName()
){}
	
	
	virtual void RegisterCommands() override;

	
	TSharedPtr<FUICommandInfo> OpenWidget;
};
