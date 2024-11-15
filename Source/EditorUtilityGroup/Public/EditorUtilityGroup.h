// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FEditorUtilityGroupModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void BuildMenu();

	bool SettingsChanged();

	void RebuildListWidget();

	void BindCommands();

	TSharedRef<SWidget> CreateSubMenu();

private:
	TSharedPtr<FUICommandList> UICommandList;

};
