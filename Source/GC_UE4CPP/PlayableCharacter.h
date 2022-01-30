#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayableCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPickItemComponent;

UCLASS()
class GC_UE4CPP_API APlayableCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayableCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;

	/*
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PickItemComponent)
		UPickItemComponent* PickItemComponent;
	*/

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
