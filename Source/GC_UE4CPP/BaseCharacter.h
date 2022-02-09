#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "BaseCharacter.generated.h"

class IInteractInterface;

UCLASS()
class GC_UE4CPP_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* InteractCapsule;

	UPROPERTY(VisibleAnywhere)
		bool bDead;

	UPROPERTY(VisibleAnywhere)
		bool bCarry;

	UPROPERTY(VisibleAnywhere)
		UCharacterMovementComponent* BaseCharacterMovement;

	UPROPERTY(VisibleAnywhere)
		float WalkSpeed;

	UPROPERTY(EditAnywhere)
		int MultiplicatorSlowSpeed;
	
	UPROPERTY(EditAnywhere)
		FName SocketName;

	IInteractInterface* InteractableObject;
	IInteractInterface* PossessedObject;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Interact();

	UFUNCTION()
		void InteractiveObjectBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void InteractiveObjectEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void SlowCharacter();

	UFUNCTION()
		void NormalSpeedCharacter();

};
