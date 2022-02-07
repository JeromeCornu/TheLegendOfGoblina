// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "AIPatrol.h"
#include "AIPatrolController.h"
#include "PickableItem.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = SpawnVolume;

	ActorToSpawn = 1;
	ActorSpawned = 0;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
	// Setup our timer between each spawn of AI
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnActors, 2.0f, true);
	// -> just do this again when you want to reajust the timer (I think)
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Limits the number of AI which will spawn 
	if (ActorSpawned == ActorToSpawn)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
	}
}

// Spawn the ennemies
void ASpawnVolume::SpawnActors()
{
	UWorld* world = GetWorld();

	// To get a random spaw Location
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

		APickableItem* Meat = world->SpawnActor<APickableItem>(MeatClassReference, SpawnMeatLocation, SpawnRotation, SpawnParams);
		AAIPatrol* Bot = world->SpawnActor<AAIPatrol>(AIClassReference, SpawnAILocation, SpawnRotation, SpawnParams);
		
		ActorSpawned++;
		Bot->Spawner = this;


		Meat->Owner = Bot;
		Meat->APickableItem::TogglePhysicsAndCollision();
		Meat->AttachToComponent(Bot->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Bot->SocketName);
		Bot->PossessedObject = Meat;
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

