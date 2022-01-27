#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractiveObjectComponent.generated.h"

class ABaseCharacter;
class UCapsuleComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GC_UE4CPP_API UInteractiveObjectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractiveObjectComponent();

	UPROPERTY(EditAnywhere)
		float InteractionRange;

	UPROPERTY(VisibleAnywhere)
		ABaseCharacter* Owner;

	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* InteractionCapsule;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Interact();

	UFUNCTION()
		virtual void InteractiveObjectBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void InteractiveObjectEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
