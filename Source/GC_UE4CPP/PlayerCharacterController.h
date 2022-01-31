#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "PlayerCharacterController.generated.h"

class APlayableCharacter;
class USpringArmComponent;

UCLASS()
class GC_UE4CPP_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	
	

	APlayerCharacterController();

	UPROPERTY(EditAnywhere, Category = CameraZoom)
		float ZoomSpeed;

	UPROPERTY(EditAnywhere, Category = CameraZoom)
		float MinZoom;

	UPROPERTY(EditAnywhere, Category = CameraZoom)
		float MaxZoom;

protected:
	APlayableCharacter* MyCharacter;

	USpringArmComponent* CameraBoom;

public:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;

	void SetupPlayerInputComponent();

	void MoveForward(float Axis);

	void MoveRight(float Axis);

	void Zoom(float Axis);
};
