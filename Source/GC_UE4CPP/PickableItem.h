// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickableItem.generated.h"

class USphereComponent;
class APlayerCharacter;

UCLASS()
class GC_UE4CPP_API APickableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableItem();

	bool isUsed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		USphereComponent* Sphere;
	
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TogglePhysicsAndCollision();

	UFUNCTION()
	void CallbackComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void CallbackComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	APlayerCharacter* Holder = nullptr;

};
