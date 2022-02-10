#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayableCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class GC_UE4CPP_API APlayableCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	//class ABaseCharacter* Parent;
	class AGC_UE4CPPGameModeBase* GameMode;

public:
	APlayableCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere, Category = Camera)
		float ZoomSpeed;

	UPROPERTY(EditAnywhere, Category = Camera)
		float MinZoom;

	UPROPERTY(EditAnywhere, Category = Camera)
		float MaxZoom;

	UFUNCTION()
		void PlayerEnd();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Axis);

	void MoveRight(float Axis);

	void Zoom(float Axis);
};
