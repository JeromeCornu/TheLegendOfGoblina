
#include "Components/StaticMeshComponent.h"
#include "BaseCharacter.h"
#include "PickableItem.h"

// Sets default values
APickableItem::APickableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the Static Mesh Component as Root
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMesh;
}

// Called when the game starts or when spawned
void APickableItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Switch physics and collisions to false/true whenever this item gets picked/thrown
void APickableItem::TogglePhysicsAndCollision()
{
	StaticMesh->SetSimulatePhysics(!StaticMesh->IsSimulatingPhysics());
	SetActorEnableCollision(!GetActorEnableCollision());
}


void APickableItem::PickUpItem()
{
	Owner->PossessedObject = this;

	TogglePhysicsAndCollision();
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Owner->SocketName);
}

void APickableItem::ThrowItem()
{
	Owner->PossessedObject = nullptr;

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	TogglePhysicsAndCollision();
}

void APickableItem::LayItemOnStand(UStaticMeshComponent* Mesh, FName Socket)
{
	Owner->PossessedObject = nullptr;
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SetActorLocationAndRotation(StaticMesh->GetSocketLocation(Socket), StaticMesh->GetSocketQuaternion(Socket));
	AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);
}

void APickableItem::TakeItemOnStand()
{
	Owner->PossessedObject = this;
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Owner->SocketName);
}

void APickableItem::Interact(ABaseCharacter* character)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Pickable Item"));

	if (character == Owner)
	{
		ThrowItem();
		Owner->InteractableObject = this;
		Owner = nullptr;
	}
	else
	{
		if (!Owner)
		{
			if (character->PossessedObject)
			{
				character->PossessedObject->Interact(character);
			}
			else
			{
				Owner = character;
				PickUpItem();
				Owner->InteractableObject = nullptr;
			}
		}
	}
}
