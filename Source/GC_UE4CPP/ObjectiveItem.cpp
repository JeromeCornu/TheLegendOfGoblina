
#include "BaseCharacter.h"
#include "PickableItem.h"
#include "ObjectiveItem.h"
#include "Goblina.h"
#include "GC_UE4CPPGameModeBase.h"

// Sets default values
AObjectiveItem::AObjectiveItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the Static Mesh Component as Root
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMesh;

	SocketName = "ItemSocket";

	DestroyDelay = 2;

	Item = nullptr;
}

// Called when the game starts or when spawned
void AObjectiveItem::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());

}

// Called every frame
void AObjectiveItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjectiveItem::Interact(ABaseCharacter* character)
{
	if (!Item && character->PossessedObject)
	{
		character->bCarry = false;
		Item = Cast<APickableItem>(character->PossessedObject);
		if (Item)
		{
			Item->LayItemOnStand(StaticMesh, SocketName);
			GoblinaRef->StartEatAnimation();
			
			GetWorld()->GetTimerManager().SetTimer(TriggerDestroyTimerHandle, this, &AObjectiveItem::TriggerDestroy, DestroyDelay);
		}
	}
}

void AObjectiveItem::TriggerDestroy()
{
	GameMode->GetaSteak();
	float NumberMeat = GameMode->GetSteaksInGame();
	GameMode->SetSteaksInGame(NumberMeat - 1);

	Item->Destroy();
	Item = nullptr;
}

