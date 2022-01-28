#pragma once

#include "CoreMinimal.h"
#include "InteractiveObjectComponent.h"
#include "PickItemComponent.generated.h"

class APickableItem;

UCLASS()
class GC_UE4CPP_API UPickItemComponent : public UInteractiveObjectComponent
{
	GENERATED_BODY()

public:
	UPickItemComponent();

	APickableItem* PickableItem;
	APickableItem* PossessedItem;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PickUpItem();

	void ThrowPossessedItem();

	virtual void Interact() override;

	virtual void InteractiveObjectBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void InteractiveObjectEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
