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
	class APlayerCharacterController* PlayerController;
	class UInGameUserWidgetclass* InGameHUD;
	class UEndScreen* UserWidgetEndScreen;
	class AAIPatrol;
	class APlayableCharacter* Player;
		
public:
	
	AGC_UE4CPPGameModeBase();
	virtual ~AGC_UE4CPPGameModeBase() = default;

	// return the number of steaks in the game
	UFUNCTION(BlueprintPure, Category = "Steaks")
		virtual float GetSteaks() const;


	//setter the number of steaks
	UFUNCTION(BlueprintCallable, Category = "Steaks")
		virtual void SetSteaks(float newSteaks);

	// return the number of steaks in the game
	UFUNCTION(BlueprintPure, Category = "Steaks")
		virtual float GetSteaksInGame() const;


	//setter the number of steaks
	UFUNCTION(BlueprintCallable, Category = "Steaks")
		virtual void SetSteaksInGame(float newSteaks);

	UFUNCTION()
		void Lose();
	UFUNCTION()
		void Victory();
	UFUNCTION()
		void GetaSteak();
	UFUNCTION()
		void PauseGame();
	
	UFUNCTION()
		float GetAI();
	UFUNCTION()
		void SetAI(float NumberAI);

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> EndScreenClass;

	UUserWidget* EndScreen;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> PauseScreenClass;

	UUserWidget* PauseScreen;

	UPROPERTY(VisibleAnywhere)
		bool bVictory;


private:
	bool GameIsPaused = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

};
