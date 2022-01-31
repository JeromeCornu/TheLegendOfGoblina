// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ProgressBar.h"
#include "InGameUserWidgetclass.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UInGameUserWidgetclass : public UUserWidget
{
	GENERATED_BODY()
protected:

	virtual void NativeConstruct() override;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* SteaksBar;
};
