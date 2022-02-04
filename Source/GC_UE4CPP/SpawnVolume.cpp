// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "AIPatrol.h"
#include "AIPatrolController.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = SpawnVolume;

	NumberToSpawn = 1;
	NumberSpawned = 0;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
	// Setup our timer between each spawn of AI
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnAI, 2.0f, true);
	// -> just do this again when you want to reajust the timer (I think)
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Limits the number of AI which will spawn 
	if (NumberSpawned == NumberToSpawn)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
	}
}

// Spawn the ennemies
void ASpawnVolume::SpawnAI()
{
	UWorld* world = GetWorld();

	// To get a random spaw Location
	FVector SpawnLocation = GetRandomLocation();

	// To get the rotation of the spawning AI
	FRotator SpawnRotation;
	SpawnRotation.Yaw = 0.f;	// X rotation
	SpawnRotation.Pitch = 0.f;	// Y rotation
	SpawnRotation.Roll = 0.f;	// Z rotation

	if (world && AIClassReference)
	{
		AAIPatrol* const Bot = world->SpawnActor<AAIPatrol>(AIClassReference, SpawnLocation, SpawnRotation);
		NumberSpawned++;
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

