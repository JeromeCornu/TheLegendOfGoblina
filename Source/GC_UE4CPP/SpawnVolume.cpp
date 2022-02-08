// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "AIPatrol.h"
#include "AIPatrolController.h"
#include "PickableItem.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = SpawnVolume;

	AISpawned = 0;
	AIOnMap = 0;
	// TODO bCanBeDestroy a mettre dans le comportement de l'IA qui fait que quand elle se dirige vers la sortie au BT elle peut etre detruite * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	bCanBeDestroy = false;

	// Set the SpawnDelay range
	SpawnDelayRangeLow = 0.0f;
	SpawnDelayRangeHigh = 5.0f;
}


void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	// Connect the overlapping function to the sphere component 
	SpawnVolume->OnComponentBeginOverlap.AddDynamic(this, &ASpawnVolume::OnOverlapDestroy);

	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnActors, 0.1f, false);
}


void ASpawnVolume::SpawnActors()
{
	UWorld* world = GetWorld();

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

		APickableItem* Meat = world->SpawnActor<APickableItem>(MeatClassReference, SpawnMeatLocation, SpawnRotation, SpawnParams);
		AAIPatrol* Bot = world->SpawnActor<AAIPatrol>(AIClassReference, SpawnAILocation, SpawnRotation, SpawnParams);
		
		if (AISpawned < 5)
		{
			AISpawned++;
		}
		AIOnMap++;
		Bot->Spawner = this;

		Meat->Owner = Bot;
		Meat->APickableItem::TogglePhysicsAndCollision();
		Meat->AttachToComponent(Bot->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Bot->SocketName);
		Bot->PossessedObject = Meat;
	}

	// Spawn the second AI, ~0 second
	if (AISpawned == 1)
	{
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnActors, 0.1f, false);
	}
	// Spawn the third AI, 60 second
	if (AISpawned == 2)
	{
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnActors, 15.0f, false);
	}
	// Spawn every 0 ~ 5 seconds when an AI exit
	if (AISpawned >= 3 && AIOnMap < 3 )
	{
		SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnActors, SpawnDelay, false);
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Created !"));
}


FVector ASpawnVolume::GetRandomLocation()
{
	FVector Origin = SpawnVolume->Bounds.Origin;	 // center of the box
	FVector Extends = SpawnVolume->Bounds.BoxExtent; // return half on the box size in a FVector

	// Get Random points in the volume spawn box
	FVector RandomPoints = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extends);

	return RandomPoints;
}


void ASpawnVolume::OnOverlapDestroy(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherComp != nullptr) && (OtherActor != this) && (Cast<AAIPatrol>(OtherActor)) && (bCanBeDestroy == true))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Overlap so destroy you !"));
		AIOnMap--;
		Destroy();
	}
}

