#include "BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "InteractiveObjectComponent.h"

// Sets default values for this component's properties
UInteractiveObjectComponent::UInteractiveObjectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	InteractionRange = 150.0f;
}

// Called when the game starts
void UInteractiveObjectComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get a reference to the BaseCharacter owning this component
	Owner = Cast<ABaseCharacter>(GetOwner());

	if (!Owner)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("cast Owner failed in PickingItemBehaviour"));
	}

	// Create the Capsule trigger that signals to a character that he can grab this item
	InteractionCapsule = NewObject<UCapsuleComponent>(this, UCapsuleComponent::StaticClass(), TEXT("Interaction Range"));
	InteractionCapsule->InitCapsuleSize(InteractionRange, 200.0f);
	InteractionCapsule->SetCollisionProfileName(TEXT("OverlapAll"));
	InteractionCapsule->RegisterComponent();
	InteractionCapsule->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

// Called every frame
void UInteractiveObjectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInteractiveObjectComponent::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Interact (Parent)"));
}

void UInteractiveObjectComponent::InteractiveObjectBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Press E to pick item (Parent)"));
}

void UInteractiveObjectComponent::InteractiveObjectEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Cannot press E to pick item anymore (Parent)"));
}

