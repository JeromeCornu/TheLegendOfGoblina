// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AMenu : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> MenuClass;


	UUserWidget* Menu;

protected:
	virtual void BeginPlay() override;

};
