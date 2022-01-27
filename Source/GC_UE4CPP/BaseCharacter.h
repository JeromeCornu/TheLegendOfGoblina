#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UInteractiveObjectComponent;

UCLASS()
class GC_UE4CPP_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	bool bDead;
	bool bInRangeOfInteractiveObject;
	bool bHaveItemInHand;

	UInteractiveObjectComponent* ComponentInInteraction;
	UInteractiveObjectComponent* ComponentUsingHand;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Interact();
};
