#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractInterface.h"

#include "PickableItem.generated.h"

class ABaseCharacter;

UCLASS()
class GC_UE4CPP_API APickableItem : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	APickableItem();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;

	ABaseCharacter* Owner;

protected:
	virtual void BeginPlay() override;


public:	
	virtual void Tick(float DeltaTime) override;

	void TogglePhysicsAndCollision();

	void PickUpItem();

	void ThrowItem();

	void LayItemOnStand(UStaticMeshComponent* Mesh, FName Socket);

	void TakeItemOnStand();

	virtual void Interact(ABaseCharacter* character) override;
};
