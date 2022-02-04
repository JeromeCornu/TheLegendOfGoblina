// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GC_UE4CPPGameModeBase.h"
#include "Components/ProgressBar.h"
#include "InGameUserWidgetclass.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UInGameUserWidgetclass : public UUserWidget
{
	GENERATED_BODY()
public: 
	class AGC_UE4CPPGameModeBase* GameMode;

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* SteaksBar;
};
