// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolSpawnerDoor.h"

// Sets default values
APatrolSpawnerDoor::APatrolSpawnerDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the Static Mesh Component as Root
	Arch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arch"));
	SetRootComponent(Arch);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APatrolSpawnerDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APatrolSpawnerDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

