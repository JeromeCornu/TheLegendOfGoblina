
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayableCharacter.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include"GC_UE4CPPGameModeBase.h"

// Sets default values
APlayableCharacter::APlayableCharacter()
{

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the component that keeps the camera to a certain distance of the character with collisions avoidance
	// and attach it to the root component
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create the camera and attach it to the end of the camera arm
	// The camera does not rotate relatively to the arm
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	ZoomSpeed = 100.0f;
	MinZoom = 300.0f;
	MaxZoom = 1000.0f;
}

// Called when the game starts or when spawned
void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, UAISense_Sight::StaticClass(), this);

}

void APlayableCharacter::PlayerEnd()
{
	ABaseCharacter::bDead = GameMode->bVictory;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("YOU WON"));

	
}


// Called every frame
void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// Get the Forward direction from the current rotation of the controller
void APlayableCharacter::MoveForward(float Axis)
{
	if (!bDead)
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

// Get the Right direction from the current rotation of the controller
void APlayableCharacter::MoveRight(float Axis)
{
	if (!bDead)
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}

void APlayableCharacter::Zoom(float Axis)
{
	if (!bDead && Axis != 0.0f)
	{
		float newTargetArmLength = CameraBoom->TargetArmLength - Axis * ZoomSpeed;
		CameraBoom->TargetArmLength = FMath::Clamp<float>(newTargetArmLength, MinZoom, MaxZoom);
	}
}