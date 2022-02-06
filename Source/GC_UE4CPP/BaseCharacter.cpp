
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/InteractInterface.h"
#include "CharactersAnimInstance.h"
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
	
	InteractCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractionCapsule"));
	InteractCapsule->SetupAttachment(RootComponent);
	InteractCapsule->InitCapsuleSize(150.0f, 200.0f);
	InteractCapsule->SetCollisionProfileName(TEXT("OverlapAll"));

	// Blocks all interactions when the character is dead
	bDead = false;

	SocketName = "ItemSocket";
	
	InteractableObject = nullptr;
	PossessedObject = nullptr;	

	//variable for the animation
	bCarry = false;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Delegates
	InteractCapsule->OnComponentBeginOverlap.AddDynamic(this, &ABaseCharacter::InteractiveObjectBeginOverlap);
	InteractCapsule->OnComponentEndOverlap.AddDynamic(this, &ABaseCharacter::InteractiveObjectEndOverlap);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Interaction with items
void ABaseCharacter::Interact()
{
	if (!bDead)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("E pressed"));
		bCarry = true;
		

		if (InteractableObject) 
		{
			bCarry = true;
			InteractableObject->Interact(this);
		}
		else if (PossessedObject)
		{
			bCarry = false;
			PossessedObject->Interact(this);
		}
		else if (!InteractableObject && !PossessedObject)
		{
			bCarry = false;
		}
		
	}
}

void ABaseCharacter::InteractiveObjectBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	InteractableObject = Cast<IInteractInterface>(OtherActor);
	if (InteractableObject)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("(ABaseCharacter) Press E to iteract with object"));		
	}
}

	
void ABaseCharacter::InteractiveObjectEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IInteractInterface* OtherInteractable = Cast<IInteractInterface>(OtherActor);
	if (InteractableObject == OtherInteractable)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("(ABaseCharacter) Cannot press E to iteract anymore"));

		InteractableObject = nullptr;
	}
}


