// Fill out your copyright notice in the Description page of Project Settings.

#include "AIPatrolTargetPoint.h"
#include "Engine/TargetPoint.h"
#include "BaseCharacter.h"
#include "PickableItem.h"
#include "StandItem.h"

// Sets default values
AStandItem::AStandItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the Static Mesh Component as Root
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMesh;

	SocketName = "ItemSocket";
}

// Called when the game starts or when spawned
void AStandItem::BeginPlay()
{
	Super::BeginPlay();

	if (TargetPointClass)
	{
		GetWorld()->SpawnActor<ATargetPoint>(TargetPointClass, StaticMesh->GetSocketLocation(SocketName), FRotator::ZeroRotator);
	}
}

// Called every frame
void AStandItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStandItem::LayItem(APickableItem* item)
{
	item->Owner->PossessedObject = nullptr;
	item->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	item->SetActorLocationAndRotation(StaticMesh->GetSocketLocation(SocketName), StaticMesh->GetSocketQuaternion(SocketName));
	item->AttachToComponent(StaticMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
}

void AStandItem::TakeItem(APickableItem* item)
{
	ABaseCharacter* character = item->Owner;
	character->PossessedObject = item;
	item->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	item->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, character->SocketName);
}

void AStandItem::Interact(ABaseCharacter* character)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Stand Item"));

	if (LaidItem)
	{
		if (character->PossessedObject) 
		{
			character->PossessedObject->Interact(character);
		}
		else 
		{
			LaidItem->Owner = character;
			TakeItem(LaidItem);
			LaidItem = nullptr;
		}
	}
	else if (character->PossessedObject)
	{
		LaidItem = Cast<APickableItem>(character->PossessedObject);
		if (LaidItem)
		{
			LayItem(LaidItem);
		}
	}

}