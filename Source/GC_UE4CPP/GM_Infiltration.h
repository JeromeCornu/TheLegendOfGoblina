// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_Infiltration.generated.h"
#include "Kismet/GameplayStatics.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AGM_Infiltration : public AGameModeBase
{

	GENERATED_BODY()

public:
		void Lose();
		void Victory();
		void LaunchTheGame();
	
};
