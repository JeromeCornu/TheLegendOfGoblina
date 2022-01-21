// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerCharacter.h"
#include "PickableItem.h"

// Sets default values
APickableItem::APickableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void APickableItem::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &APickableItem::CallbackComponentBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &APickableItem::CallbackComponentEndOverlap);
}

// Called every frame
void APickableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickableItem::TogglePhysicsAndCollision()
{
	StaticMesh->SetSimulatePhysics(!StaticMesh->IsSimulatingPhysics());
	SetActorEnableCollision(!GetActorEnableCollision());
}

void APickableItem::CallbackComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Press E to pick item"));
	
	Holder = (APlayerCharacter*)OtherActor;
	if (Holder) 
	{
		Holder->PickableItem = this;
	}
}

void APickableItem::CallbackComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Cannot press E to pick item anymore"));
	
	Holder = (APlayerCharacter*)OtherActor;
	if (Holder)
	{
		Holder->PickableItem = nullptr;
	}
}

