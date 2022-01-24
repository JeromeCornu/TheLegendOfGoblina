#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PickableItem.h"
#include "BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize capsule size
	GetCapsuleComponent()->InitCapsuleSize(50.0f, 160.0f);


	// Not to allow the character to rotate itself
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Orient character to movement and set up rotation rate
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	// Blocks all interactions when the character is dead
	bDead = false;

	// Item in range of being picked up
	PickableItem = nullptr;

	// Current possessed item
	PossessedItem = nullptr;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Pick up in range item
void ABaseCharacter::PickUpItem()
{
	PossessedItem = PickableItem;
	PossessedItem->TogglePhysicsAndCollision();
	PossessedItem->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("ItemSocket"));

	PickableItem = nullptr;
}

// Throw the current possessed item
void ABaseCharacter::ThrowPossessedItem()
{
	PickableItem = PossessedItem;

	PossessedItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	PossessedItem->TogglePhysicsAndCollision();
	PossessedItem = nullptr;
}

// Interaction with items
void ABaseCharacter::OnBeginInteract()
{
	if (!bDead) 
	{
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
}

