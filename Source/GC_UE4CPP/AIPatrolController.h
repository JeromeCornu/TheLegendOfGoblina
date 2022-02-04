// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIPatrolController.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API AAIPatrolController : public AAIController
{
	GENERATED_BODY()

		//Behavior tree component
		UBehaviorTreeComponent* BehaviorComp;

		// Our blackboard component
		UBlackboardComponent* BlackboardComp;

		// Blackboard keys
		UPROPERTY(EditDefaultsOnly, Category = "AI") // reference to the goal location
			FName LocationToGoKey;

		UPROPERTY(EditDefaultsOnly, Category = "AI") // reference to the player location
			FName PlayerKey;

		TArray<AActor*> PatrolPoints;

		void OnPossess(APawn* InPawn); // function called when possess a pawn


public:

	AAIPatrolController();

	void SetPlayerCaught(APawn* _Pawn);

	int32 CurrentPatrolPoint = 0;

	// Inline getter Functions

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }
	// FORCEINLINE --> forces compiler to do inline unconditionally

	UFUNCTION()
		virtual void BeginPlay();
};
