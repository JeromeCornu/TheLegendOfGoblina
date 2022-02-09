// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "SpawnVolume.h"
#include "AIPatrol.generated.h"

UCLASS()
class GC_UE4CPP_API AAIPatrol : public ABaseCharacter
{
	GENERATED_BODY()
		class AGC_UE4CPPGameModeBase* GameMode;

public:
	AAIPatrol();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	// Collision sphere to detect when the player has been catch
	UPROPERTY(VisibleAnywhere, Category = "AI")
		class USphereComponent* MyCollisionSphere;

	// Size of the sphere collision
	float SphereRadius;

	ASpawnVolume* Spawner;

	void Despawn();

private:

	// Called when the player has been touch
	UFUNCTION()
		void OnPlayerCatch(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
