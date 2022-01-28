#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InteractiveObjectComponent.h"
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
	bInRangeOfInteractiveObject = false;
	bHaveItemInHand = false;
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

// Interaction with items
void ABaseCharacter::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("E pressed"));
	if (!bDead) 
	{
		if (bHaveItemInHand)
		{
			ComponentUsingHand->Interact();
		}
		else if (bInRangeOfInteractiveObject)
		{
			ComponentInInteraction->Interact();
		}
	}
}

