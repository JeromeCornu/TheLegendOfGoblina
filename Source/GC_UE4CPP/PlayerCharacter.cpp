// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableItem.h"
#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize capsule size
	GetCapsuleComponent()->InitCapsuleSize(PlayerRadius, CapsuleHalfHeight);

	// Not to allow the character to rotate itself
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Orient character to movement and set up rotation rate
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(CharacterPitchRate, CharacterYawRate, CharacterRollRate);
	
	// No jump

	// Create the component that keeps the camera to a certain distance of the character with collisions avoidance
	// and attach it to the root component
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = CameraArmLength;
	CameraBoom->bUsePawnControlRotation = true;

	// Create the camera and attach it to the end of the camera arm
	// The camera does not rotate relatively to the arm
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bDead = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind mouse and keyboard inputs : you need to add axis mappings in project settings->inputs
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Interact",IE_Pressed, this, &APlayerCharacter::OnBeginInteract);

}

// Get the Forward direction from the current rotation of the controller
void APlayerCharacter::MoveForward(float Axis)
{
	if (!bDead) 
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

// Get the Right direction from the current rotation of the controller
void APlayerCharacter::MoveRight(float Axis)
{
	if (!bDead) 
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}

void APlayerCharacter::OnBeginInteract() 
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("E pressed"));

	if(PossessedItem) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("PossessedItem"));
	if(PickableItem) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("PickableItem"));

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

void APlayerCharacter::PickUpItem()
{
	PossessedItem = PickableItem;
	PossessedItem->TogglePhysicsAndCollision();
	PossessedItem->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("ItemSocket"));
	
	PickableItem = nullptr;
}

void APlayerCharacter::ThrowPossessedItem()
{
	PickableItem = PossessedItem;

	PossessedItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	PossessedItem->TogglePhysicsAndCollision();
	PossessedItem = nullptr;
}
