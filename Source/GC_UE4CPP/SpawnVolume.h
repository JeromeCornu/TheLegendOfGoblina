// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "SpawnVolume.generated.h"

UCLASS()
class GC_UE4CPP_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	// A class reference for AIPatrol
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Reference", meta = (AllowPrivateAccess = true))
		TSubclassOf<class AAIPatrol> AIClassReference;

	// A class reference for PickableItem
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Reference", meta = (AllowPrivateAccess = true))
		TSubclassOf<class APickableItem> MeatClassReference;

	// A BoxComponent which act as spawn volume to spawn
	UPROPERTY(EditAnywhere, Category = "Components")
		UBoxComponent* SpawnVolume;

	// Timer used to calcul time between each spawn
		FTimerHandle SpawnTimer;

	// Number of units to spawn
	UPROPERTY(EditAnywhere, Category = "Spawn specificities")
		int32 ActorToSpawn;
	// Number of units already spawned
	UPROPERTY(VisibleAnywhere, Category = "Spawn specificities")
		int32 ActorSpawned;

	// Used to spawn Actors
	UFUNCTION()
		void SpawnActors();

	// Used to returns a FVector which has random location coordinates
	UFUNCTION()
		FVector GetRandomLocation();

};
