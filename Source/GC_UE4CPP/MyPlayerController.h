// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 *
 */
UCLASS()
class GC_UE4CPP_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()


protected:

	UPROPERTY(EditAnywhere)

		TSubclassOf<UUserWidget> ExampleUIClass;

	UUserWidget* ExampleUI;

	virtual void BeginPlay() override;

};
