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

	// Detection of the player
	UPROPERTY(VisibleAnywhere, Category = "AI")
		class UPawnSensingComponent* PawnSensingComp;

	// Collision sphere to detect when the player has been catch
	UPROPERTY(VisibleAnywhere, Category = "AI")
		class USphereComponent* MyCollisionSphere;

	// Size of the sphere collision
	float SphereRadius;


private:

	// Called when the player has been see
	UFUNCTION()
		void OnPlayerCaught(APawn* Pawn);

	// Called when the player has been touch
	UFUNCTION()
		void OnPlayerCatch(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
