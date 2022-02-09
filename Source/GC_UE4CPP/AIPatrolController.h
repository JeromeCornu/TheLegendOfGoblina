// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AIPerceptionTypes.h"

#include "AIPatrolController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class GC_UE4CPP_API AAIPatrolController : public AAIController
{
	GENERATED_BODY()

public:
	AAIPatrolController();

	UPROPERTY(VisibleAnywhere, Category = "AI")
		UAIPerceptionComponent* PerceptionComp;

	UPROPERTY(VisibleAnywhere, Category = "AI")
		UAISenseConfig_Sight* SightConfig;

	// Blackboard keys
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName PlayerKey;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName PossessFoodKey;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName InvestigateLocationKey;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName ExitKey;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName IsPatrollingKey;
	
	UPROPERTY(EditAnywhere, Category = "AI")
		bool bIsPatrolling;

	AActor* ExitActor;

	TArray<AActor*> Plates;
	int32 PlateIndex = 0;

	// Inline getter Functions
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return Blackboard; }
	FORCEINLINE TArray<AActor*> GetPlatesArray() const { return Plates; }

	// function called when possess a pawn
	void OnPossess(APawn* InPawn);

	// function called when possess a pawn
	void OnUnPossess();

	UFUNCTION()
		void OnSee(AActor* Actor, FAIStimulus Stimulus);


protected:
	virtual void BeginPlay() override;

};
