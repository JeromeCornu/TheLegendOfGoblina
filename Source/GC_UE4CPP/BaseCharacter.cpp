
#include "BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/InteractInterface.h"
#include "CharactersAnimInstance.h"

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

	// Variables of Character's speed
	BaseCharacterMovement = GetCharacterMovement();
	WalkSpeed = BaseCharacterMovement->MaxWalkSpeed;

	MultiplicatorSlowSpeed = 2;

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
		if (InteractableObject) 
		{
			InteractableObject->Interact(this);
		}
		else if (PossessedObject)
		{
			PossessedObject->Interact(this);
		}
	}
}

void ABaseCharacter::InteractiveObjectBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	InteractableObject = Cast<IInteractInterface>(OtherActor);
}

	
void ABaseCharacter::InteractiveObjectEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IInteractInterface* OtherInteractable = Cast<IInteractInterface>(OtherActor);
	if (InteractableObject == OtherInteractable)
	{
		InteractableObject = nullptr;
	}
}

void ABaseCharacter::SlowCharacter()
{
	BaseCharacterMovement->MaxWalkSpeed = WalkSpeed / MultiplicatorSlowSpeed;
}

void ABaseCharacter::NormalSpeedCharacter()
{
	BaseCharacterMovement->MaxWalkSpeed = WalkSpeed;
}



