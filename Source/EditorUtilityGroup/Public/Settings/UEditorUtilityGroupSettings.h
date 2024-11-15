#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UEditorUtilityGroupSettings.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI, config=Editor,DefaultConfig, meta =(DisplayName ="Editor Utility Group Setting",CategoryName ="Editor Utility Group Setting"))
class UEditorUtilityGroupSettings : public UObject
{
	GENERATED_BODY()

	UEditorUtilityGroupSettings(const FObjectInitializer& ObjectInitializer);
public:

	UPROPERTY(EditAnywhere,BlueprintReadOnly, config, Category = "Editor Utility Group Settings")
	TArray<FString> ListWidgetPath;


#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
	
};

