
#include "StandItem.h"
#include "BaseCharacter.h"
#include "PickableItem.h"

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
}

// Called every frame
void AStandItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStandItem::Interact(ABaseCharacter* character)
{
	if (LaidItem)
	{
		if (character->PossessedObject) 
		{
			character->bCarry = false;
			character->PossessedObject->Interact(character);
		}
		else 
		{
			character->bCarry = true;
			LaidItem->Owner = character;
			LaidItem->TakeItemOnStand();
			LaidItem = nullptr;
		}
	}
	else if (character->PossessedObject)
	{
		character->bCarry = false;
		LaidItem = Cast<APickableItem>(character->PossessedObject);
		if (LaidItem)
		{
			LaidItem->LayItemOnStand(StaticMesh, SocketName);
		}
	}
}