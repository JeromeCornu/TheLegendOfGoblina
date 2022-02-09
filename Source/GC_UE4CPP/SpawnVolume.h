// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "SpawnVolume.generated.h"

class AAIPatrol;
class AAIPatrolController;
class APickableItem;
UCLASS()
class GC_UE4CPP_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
		class AGC_UE4CPPGameModeBase* GameMode;

public:	
	ASpawnVolume();

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Arch;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Door;
	
	// Class references
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Reference", meta = (AllowPrivateAccess = true))
		TSubclassOf<AAIPatrol> AIClassReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Reference", meta = (AllowPrivateAccess = true))
		TSubclassOf<APickableItem> MeatClassReference;

	UPROPERTY(VisibleAnywhere, Category = "AI Reference")
		AAIPatrol* Bot;

	UPROPERTY(VisibleAnywhere, Category = "AI Reference")
		AAIPatrolController* BotController;


	// A BoxComponent which act as spawner
	UPROPERTY(EditAnywhere, Category = "Components")
		UBoxComponent* SpawnVolume;

	// BB's values
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName IsPatrollingKey;


	// Timer
	UPROPERTY(VisibleAnywhere, Category = "Components")
		FTimerHandle SpawnTimer;

	UPROPERTY(EditAnywhere, Category = "Spawn specificities")
		float SpawnDelayRangeLow;

	UPROPERTY(EditAnywhere, Category = "Spawn specificities")
		float SpawnDelayRangeHigh;

	UPROPERTY(VisibleAnywhere, Category = "Spawn specificities")
		float SpawnDelay;


	// Number of Actors
	UPROPERTY(EditAnywhere, Category = "Spawn specificities")
		float NumberMeat;

	UPROPERTY(VisibleAnywhere, Category = "Spawn specificities")
		float NumberAI;

	UPROPERTY(EditAnywhere, Category = "Spawn specificities")
		int32 ActorToSpawn;

	UPROPERTY(VisibleAnywhere, Category = "Spawn specificities")
		int32 AISpawned;


	// Properties of Actors
	UPROPERTY(VisibleAnywhere, Category = "Spawn specificities")
		FVector SpawnLocation;

	UPROPERTY(VisibleAnywhere, Category = "Spawn specificities")
		FVector SpawnMeatLocation;

	UPROPERTY(VisibleAnywhere, Category = "Spawn specificities")
		FRotator SpawnRotation;


	UFUNCTION()
		void SpawnActors();

	UFUNCTION()
		void SpawnMeat();

	UFUNCTION()
		void TimerBeforeNextSpawn();

	// Used to returns a FVector which has random location coordinates
	UFUNCTION()
		FVector GetRandomLocation();

};
