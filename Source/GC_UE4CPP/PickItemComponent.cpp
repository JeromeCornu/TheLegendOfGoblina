#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "BaseCharacter.h"
#include "PickableItem.h"
#include "PickItemComponent.h"

// Sets default values for this component's properties
UPickItemComponent::UPickItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Item in range of being picked up
	PickableItem = nullptr;

	// Current possessed item
	PossessedItem = nullptr;
}

// Called when the game starts
void UPickItemComponent::BeginPlay()
{
	Super::BeginPlay();

	// Delegates
	InteractionCapsule->OnComponentBeginOverlap.AddDynamic(this, &UPickItemComponent::InteractiveObjectBeginOverlap);
	InteractionCapsule->OnComponentEndOverlap.AddDynamic(this, &UPickItemComponent::InteractiveObjectEndOverlap);

	// Get a reference to the SkeletalMesh of the character owning this component
	Mesh = Cast<ACharacter>(GetOwner())->GetMesh();
}


// Called every frame
void UPickItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPickItemComponent::PickUpItem()
{
	PossessedItem = PickableItem;
	PossessedItem->TogglePhysicsAndCollision();
	PossessedItem->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("ItemSocket"));

	PickableItem = nullptr;
	/*
	Owner->bHaveItemInHand = true;
	Owner->ComponentUsingHand = this;
	*/
}

void UPickItemComponent::ThrowPossessedItem()
{
	/*
	Owner->bHaveItemInHand = false;
	Owner->ComponentUsingHand = nullptr;
	*/

	PickableItem = PossessedItem;

	PossessedItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	PossessedItem->TogglePhysicsAndCollision();
	PossessedItem = nullptr;
}

void UPickItemComponent::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, TEXT("Interact (Child)"));

	if (PossessedItem)
	{
		ThrowPossessedItem();
	}
	else
	{
		if (PickableItem)
		{
			PickUpItem();
		}
	}
}

void UPickItemComponent::InteractiveObjectBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, TEXT("Press E to pick item (Child)"));
	PickableItem = Cast<APickableItem>(OtherActor);
	if (PickableItem)
	{
		/*
		Owner->bInRangeOfInteractiveObject = true;
		Owner->ComponentInInteraction = this;
		*/
	}
}

void UPickItemComponent::InteractiveObjectEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, TEXT("Cannot press E to pick item anymore (Child)"));
	if (Cast<APickableItem>(OtherActor))
	{
		/*
		PickableItem = nullptr;
		Owner->bInRangeOfInteractiveObject = false;
		Owner->ComponentInInteraction = nullptr;
		*/
	}
}

