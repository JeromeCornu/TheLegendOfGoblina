#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickableItem.generated.h"

UCLASS()
class GC_UE4CPP_API APickableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	APickableItem();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void TogglePhysicsAndCollision();
};
