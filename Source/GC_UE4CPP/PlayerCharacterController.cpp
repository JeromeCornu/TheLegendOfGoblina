// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "BaseCharacter.h"
#include "PlayableCharacter.h"
#include "PlayerCharacterController.h"

APlayerCharacterController::APlayerCharacterController()
{
	ZoomSpeed = 100.0f;
	MinZoom = 300.0f;
	MaxZoom = 1000.0f;

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
		CameraBoom = MyCharacter->CameraBoom;
	}
}

// Called to bind functionality to input
void APlayerCharacterController::SetupPlayerInputComponent()
{
	SetupInputComponent();

	// Bind mouse and keyboard inputs : you need to add axis mappings in project settings->inputs
	InputComponent->BindAxis("Turn", MyCharacter, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", MyCharacter, &APawn::AddControllerPitchInput);

	InputComponent->BindAxis("MoveForward", this, &APlayerCharacterController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacterController::MoveRight);

	InputComponent->BindAxis("Zoom", this, &APlayerCharacterController::Zoom);

	InputComponent->BindAction("Interact", IE_Pressed, MyCharacter, &ABaseCharacter::Interact);
}

// Get the Forward direction from the current rotation of the controller
void APlayerCharacterController::MoveForward(float Axis)
{
	if (!MyCharacter->bDead)
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		MyCharacter->AddMovementInput(Direction, Axis);
	}
}

// Get the Right direction from the current rotation of the controller
void APlayerCharacterController::MoveRight(float Axis)
{
	if (!MyCharacter->bDead)
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		MyCharacter->AddMovementInput(Direction, Axis);
	}
}

void APlayerCharacterController::Zoom(float Axis)
{
	if (!MyCharacter->bDead && Axis != 0.0f)
	{
		float newTargetArmLength = CameraBoom->TargetArmLength - Axis * ZoomSpeed;
		CameraBoom->TargetArmLength = FMath::Clamp<float>(newTargetArmLength, MinZoom, MaxZoom);
	}
}