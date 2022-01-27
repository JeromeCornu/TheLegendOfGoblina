// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "EndScreen.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AEndScreen : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> EndScreenClass;


	UUserWidget* EndScreen;

protected:
	virtual void BeginPlay() override;
};
