// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public: 
	AMyGameStateBase();
	virtual ~AMyGameStateBase() = default;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		int32 NumberOfSteaks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 NumberOfAI;

};
