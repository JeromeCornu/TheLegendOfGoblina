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
	SetRootComponent(SpawnVolume);

	// Create the Static Mesh Component as Root
	Arch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arch"));
	Arch->SetupAttachment(RootComponent);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(Arch);

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

	GameMode->DelegateDestroy.AddDynamic(this, &ASpawnVolume::TimerBeforeNextSpawn);

	GetWorldTimerManager().SetTimer(SpawnTimerStarting, this, &ASpawnVolume::SpawnActors, 0.1f, false);
}

void ASpawnVolume::Tick(float Delta)
{
	Super::Tick(Delta);
}


void ASpawnVolume::SpawnActors()
{	
	// Get Informations about the map
	NumberOfSteaksInGame = GameMode->GetSteaksInGame();
	NumberAI = GameMode->GetAI();

	SpawnLocation = GetRandomLocation();

	if (GetWorld() && AIClassReference && MeatClassReference)
	{
		// Spawning action
		FActorSpawnParameters SpawnParamsAI;
		SpawnParamsAI.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		Bot = GetWorld()->SpawnActor<AAIPatrol>(AIClassReference, SpawnLocation, FRotator::ZeroRotator, SpawnParamsAI);
		BotController = Bot->GetController<AAIPatrolController>();

		// Setting parameters
		GameMode->SetAI(NumberAI + 1);

		Bot->Spawner = this;

		BotController->GetBlackboardComp()->SetValueAsBool(IsPatrollingKey, true);
		BotController->bIsPatrolling = true;

		if (NumberOfSteaksInGame < 5)
		{
			SpawnMeat();
		}
		if (AISpawned < 5)
		{
			// to avoid having an unnecessarily large number of AISpawned
			AISpawned++;
		}
	}
	// Recale the function for the 1st three IA
	if (AISpawned == 1)
	{
		// 0 scd for the 2nd AI
		GetWorldTimerManager().SetTimer(SpawnTimerStarting, this, &ASpawnVolume::SpawnActors, 0.1f, false);
	}
	else if (AISpawned == 2)
	{
		// 60 scd for the 3rd AI
		GetWorldTimerManager().SetTimer(SpawnTimerStarting, this, &ASpawnVolume::SpawnActors, 60.0f, false);
	}
}

void ASpawnVolume::SpawnMeat()
{
	FActorSpawnParameters SpawnParamsMeat;
	SpawnParamsMeat.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	APickableItem* Meat = GetWorld()->SpawnActor<APickableItem>(MeatClassReference, SpawnLocation, FRotator::ZeroRotator, SpawnParamsMeat);

	Meat->Owner = Bot;
	Meat->APickableItem::TogglePhysicsAndCollision();
	Meat->AttachToComponent(Bot->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Bot->SocketName);

	Bot->PossessedObject = Meat;
	Bot->bCarry = true;
	Bot->ABaseCharacter::SlowCharacter();

	GameMode->SetSteaksInGame(NumberOfSteaksInGame + 1);

	BotController->GetBlackboardComp()->SetValueAsBool(IsPatrollingKey, false);
	BotController->bIsPatrolling = false;
}


void ASpawnVolume::TimerBeforeNextSpawn()
{
	// Call SpawnActor every 0 ~ 5 seconds when an AI exit
	SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
	FTimerHandle SpawnTimer;
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnActors, SpawnDelay, false);
}


FVector ASpawnVolume::GetRandomLocation()
{
	FVector Origin = SpawnVolume->Bounds.Origin;	 // center of the box
	FVector Extends = SpawnVolume->Bounds.BoxExtent; // return half on the box size in a FVector

	// Get Random points in the volume spawn box
	FVector RandomPoints = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extends);

	return RandomPoints;
}
