// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GC_UE4CPPGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AGC_UE4CPPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	class UInGameUserWidgetclass* InGameHUD;
		
public:

	AGC_UE4CPPGameModeBase();
	virtual ~AGC_UE4CPPGameModeBase() = default;

	// return the number of steaks in the game
	UFUNCTION(BlueprintPure, Category = "Steaks")
		virtual int32 GetSteaks() const;


	//setter the number of steaks
	UFUNCTION(BlueprintCallable, Category = "Steaks")
		virtual void SetSteaks(int32 newSteaks);

	UFUNCTION()
		void Lose();
	UFUNCTION()
		void Victory();
	UFUNCTION()
		void GetaSteak();
	UFUNCTION()
		void PauseGame();

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> EndScreenClass;

	UUserWidget* EndScreen;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> PauseScreenClass;

	UUserWidget* PauseScreen;


private:
	bool GameIsPaused = false;

	

};
