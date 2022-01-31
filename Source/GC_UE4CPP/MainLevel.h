// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainLevel.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AMainLevel : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> InGameHUDClass;


	UUserWidget* InGameHUD;

protected:
	virtual void BeginPlay() override;
};
