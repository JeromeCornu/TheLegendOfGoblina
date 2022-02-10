// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "AIPatrol.h"
#include "AIPatrolController.h"
#include "PickableItem.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

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

	// Set the SpawnDelay range
	SpawnDelayRangeLow = 0.0f;
	SpawnDelayRangeHigh = 5.0f;

	IsPatrollingKey = "IsPatrolling";
}


void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnActors, 0.1f, false);
}


void ASpawnVolume::SpawnActors()
{	
	// NumberOfSteaksInGame = GameMode->GetSteaksInGame(); !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	NumberAI = GameMode->GetAI();

	SpawnLocation = GetRandomLocation();

	// To get the rotation of the spawning AI
	SpawnRotation.Yaw = 0.f;	// X rotation
	SpawnRotation.Pitch = 0.f;	// Y rotation
	SpawnRotation.Roll = 0.f;	// Z rotation

	if (GetWorld() && AIClassReference && MeatClassReference)
	{
		FActorSpawnParameters SpawnParamsAI;
		SpawnParamsAI.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		Bot = GetWorld()->SpawnActor<AAIPatrol>(AIClassReference, SpawnLocation, SpawnRotation, SpawnParamsAI);
		BotController = Bot->GetController<AAIPatrolController>();

		GameMode->SetAI(NumberAI + 1);

		Bot->Spawner = this;

		BotController->GetBlackboardComp()->SetValueAsBool(IsPatrollingKey, true);
		BotController->bIsPatrolling = true;

		if (NumberOfSteaksInGame < 5)
		{
			SpawnMeat();
		}
		// to avoid having an unnecessarily large number of AISpawned
		if (AISpawned < 5)
		{
			AISpawned++;
		}
		GameMode->SetAI(NumberAI + 1);
	}

	TimerBeforeNextSpawn();
}

void ASpawnVolume::SpawnMeat()
{
	FActorSpawnParameters SpawnParamsMeat;
	SpawnParamsMeat.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	APickableItem* Meat = GetWorld()->SpawnActor<APickableItem>(MeatClassReference, SpawnLocation, SpawnRotation, SpawnParamsMeat);

	Meat->Owner = Bot;
	Meat->APickableItem::TogglePhysicsAndCollision();
	Meat->AttachToComponent(Bot->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Bot->SocketName);

	Bot->PossessedObject = Meat;
	Bot->bCarry = true;
	Bot->ABaseCharacter::SlowCharacter();

	// GameMode->SetSteaksInGame(NumberOfSteaksInGame + 1); !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	BotController->GetBlackboardComp()->SetValueAsBool(IsPatrollingKey, false);
	BotController->bIsPatrolling = false;
}


void ASpawnVolume::TimerBeforeNextSpawn()
{
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
	if (AISpawned >= 3 && NumberAI < 3)
	{
		SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnActors, SpawnDelay, false);
	}
	if (NumberOfSteaksInGame >= 5)
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
