// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIPatrol.generated.h"

UCLASS()
class GC_UE4CPP_API AAIPatrol : public ACharacter
{
	GENERATED_BODY()

public:
	AAIPatrol();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "IA")
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, Category = "AI")
		class UPawnSensingComponent* PawnSensingComp;

	// la
	UPROPERTY(VisibleAnywhere, Category = "AI")
		class USphereComponent* MyCollisionSphere;


	float SphereRadius;
	// a la


private:

	UFUNCTION()
		void OnPlayerCaught(APawn* Pawn);

	
	UFUNCTION()
		void OnPlayerCatch(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
