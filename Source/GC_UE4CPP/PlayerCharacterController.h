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

protected:
	APlayableCharacter* MyCharacter;

public:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;

	void SetupPlayerInputComponent();

};
