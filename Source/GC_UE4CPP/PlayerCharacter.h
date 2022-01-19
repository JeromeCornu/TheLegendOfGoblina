// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/UserWidget.h"

#include "PlayerCharacter.generated.h"

UCLASS()
class GC_UE4CPP_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	UPROPERTY(EditAnywhere)
	float CapsuleHalfHeight = 160.0f;

	UPROPERTY(EditAnywhere)
	float PlayerRadius = 50.0f;

	UPROPERTY(EditAnywhere)
	float CharacterPitchRate = 0.0f;

	UPROPERTY(EditAnywhere)
	float CharacterYawRate = 540.0f;

	UPROPERTY(EditAnywhere)
	float CharacterRollRate = 0.0f;

	UPROPERTY(EditAnywhere)
	float CameraArmLength = 300.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;

	void MoveForward(float Axis);

	void MoveRight(float Axis);

	bool bDead;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
