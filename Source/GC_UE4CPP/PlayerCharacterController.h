#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "PlayerCharacterController.generated.h"

class APlayableCharacter;
class USpringArmComponent;
class AHUD;

UCLASS()
class GC_UE4CPP_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> InGameHUDClass;


	UUserWidget* InGameHUD;
		

	APlayerCharacterController();

protected:
	APlayableCharacter* MyCharacter;

public:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;

	void SetupPlayerInputComponent();

};
