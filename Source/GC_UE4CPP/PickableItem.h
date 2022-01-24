#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickableItem.generated.h"

class USphereComponent;
class ABaseCharacter;

UCLASS()
class GC_UE4CPP_API APickableItem : public AActor
{
	GENERATED_BODY()
	
public:	

	APickableItem();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		USphereComponent* Sphere;
	
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;
	
public:	

	virtual void Tick(float DeltaTime) override;

	void TogglePhysicsAndCollision();

	UFUNCTION()
	void CallbackComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void CallbackComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
