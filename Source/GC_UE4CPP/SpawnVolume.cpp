// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "AIPatrol.h"
#include "AIPatrolController.h"
#include "PickableItem.h"
#include "GC_UE4CPPGameModeBase.h"
#include "BaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = SpawnVolume;

	AISpawned = 0;
	NumberAIOnMap = 0;

	// Set the SpawnDelay range
	SpawnDelayRangeLow = 0.0f;
	SpawnDelayRangeHigh = 5.0f;
}


void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnActors, 0.1f, false);
}


void ASpawnVolume::SpawnActors()
{
	UWorld* world = GetWorld();
	
	AGC_UE4CPPGameModeBase* GameMode = world->GetAuthGameMode<AGC_UE4CPPGameModeBase>();
	NumberMeat = GameMode->GetSteaks();
	//GameMode->GetAI();

	FVector SpawnAILocation = GetRandomLocation();
	FVector SpawnMeatLocation = SpawnAILocation + (0.f, 0.f, 1.f);

	// To get the rotation of the spawning AI
	FRotator SpawnRotation;
	SpawnRotation.Yaw = 0.f;	// X rotation
	SpawnRotation.Pitch = 0.f;	// Y rotation
	SpawnRotation.Roll = 0.f;	// Z rotation

	if (world && AIClassReference && MeatClassReference)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


		AAIPatrol* Bot = world->SpawnActor<AAIPatrol>(AIClassReference, SpawnAILocation, SpawnRotation, SpawnParams);
		
		Bot->Spawner = this;
		// Bot->bIsPatrolling = true;

		// if there is less than 5 meats, spawn AI with Meat
		if (NumberMeat < 5)
		{
			APickableItem* Meat = world->SpawnActor<APickableItem>(MeatClassReference, SpawnMeatLocation, SpawnRotation, SpawnParams);

			Meat->Owner = Bot;
			Meat->APickableItem::TogglePhysicsAndCollision();
			Meat->AttachToComponent(Bot->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Bot->SocketName);

			Bot->PossessedObject = Meat;
			Bot->ABaseCharacter::SlowCharacter();
			Bot->bCarry = true;						// PB les ia ramassent !!!!

			GameMode->SetSteaks(NumberMeat + 1);
			// baisser le nb de MeatOnMap quand elles sont mangé par la Gobelina
			
			// Bot->bIsPatrolling = false;
		}

		if (AISpawned < 5)
		{
			AISpawned++;
		}

		NumberAIOnMap++;
		// baisser le nb de NumberAIOnMap quand elles sont detruite dans le BTDestroy
	}

	// Spawn the second AI, ~0 second
	if (AISpawned == 1)
	{
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnActors, 0.1f, false);
	}
	// Spawn the third AI, 60 second
	if (AISpawned == 2)
	{
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnActors, 60.0f, false);
	}
	// Spawn every 0 ~ 5 seconds when an AI exit
	if (AISpawned >= 3 && NumberAIOnMap < 3 )
	{
		SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnActors, SpawnDelay, false);
	}
	if (NumberMeat >= 5)
	{
		// Bot->bIsPatrolling = true;
	}

}


FVector ASpawnVolume::GetRandomLocation()
{
	FVector Origin = SpawnVolume->Bounds.Origin;	 // center of the box
	FVector Extends = SpawnVolume->Bounds.BoxExtent; // return half on the box size in a FVector

	// Get Random points in the volume spawn box
	FVector RandomPoints = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extends);

	return RandomPoints;
}
