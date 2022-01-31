// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "BaseCharacter.h"
#include "PlayableCharacter.h"
#include "PlayerCharacterController.h"

APlayerCharacterController::APlayerCharacterController()
{
	
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();
}

// Reference the player character when possessing it
void APlayerCharacterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	MyCharacter = Cast<APlayableCharacter>(InPawn);

	if (MyCharacter) 
	{
		SetupPlayerInputComponent();
	}
}

// Called to bind functionality to input
void APlayerCharacterController::SetupPlayerInputComponent()
{
	SetupInputComponent();

	// Bind mouse and keyboard inputs : you need to add axis mappings in project settings->inputs
	InputComponent->BindAxis("Turn", MyCharacter, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", MyCharacter, &APawn::AddControllerPitchInput);

	InputComponent->BindAxis("MoveForward", MyCharacter, &APlayableCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", MyCharacter, &APlayableCharacter::MoveRight);

	InputComponent->BindAxis("Zoom", MyCharacter, &APlayableCharacter::Zoom);

	InputComponent->BindAction("Interact", IE_Pressed, MyCharacter, &ABaseCharacter::Interact);
}
