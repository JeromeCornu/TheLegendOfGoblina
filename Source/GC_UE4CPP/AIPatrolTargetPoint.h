// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "AIPatrolTargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AAIPatrolTargetPoint : public ATargetPoint
{
	GENERATED_BODY()

	
public:
	AAIPatrolTargetPoint();

public:

	// Collision sphere to detect when a aliment is close
	UPROPERTY(VisibleAnywhere, Category = "Plate")
		class USphereComponent* MyCollisionSphere;

	// Size of the sphere collision
	float SphereRadius;

	UPROPERTY(EditAnywhere, Category = "Plate")
		FVector NewLocation;

	UPROPERTY(EditAnywhere, Category = "Plate")
		FRotator NewRotation;


private:

	// Called when a aliment is close
	UFUNCTION()
		void OnSteakClose(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
