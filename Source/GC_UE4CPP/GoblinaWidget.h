// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GoblinaWidget.generated.h"

/**
 *
 */
UCLASS(Abstract)
class GC_UE4CPP_API UGoblinaInterface : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* NameOfGoblina;

};
