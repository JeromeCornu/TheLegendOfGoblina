#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PickItemComponent.h"
#include "PlayableCharacter.h"

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

	//PickItemComponent = CreateDefaultSubobject<UPickItemComponent>(TEXT("PickItemComponent"));
}

// Called when the game starts or when spawned
void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}