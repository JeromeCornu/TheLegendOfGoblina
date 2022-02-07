// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPatrolController.h"
#include "AIPatrol.h"
#include "AIPatrolTargetPoint.h"
#include "BTPickUpMeat.h"
#include "SpawnVolume.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Controller.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Result of beeing see + connection with the BB and the BT
AAIPatrolController::AAIPatrolController()
{
	// Initialize blackboard keys
	PlayerKey = "Player";
	LocationToGoKey = "LocationToGo";
	ExitPointKey = "ExitPoint";
	PossessMeatKey = "PossessMeat";

	CurrentPatrolPoint = 0;	
}

// The player has been see -> set a key on the blackboard
void AAIPatrolController::SetPlayerCaught(APawn* _Pawn)
{
	if (Blackboard)
	{
		Blackboard->SetValueAsObject(PlayerKey, _Pawn);
	}
}

void AAIPatrolController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Get reference to the character
	AAIPatrol* AICharacter = Cast<AAIPatrol>(InPawn);
	UE_LOG(LogTemp, Warning, TEXT("OnPossess AI"));

	AActor* ExitPoint = UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnVolume::StaticClass());

	// Initialize the BehaviorTree's value : PossessMeat
	bool bValue = true;

	if (AICharacter)
	{
		RunBehaviorTree(AICharacter->BehaviorTree);

		if (Blackboard)
		{
			// Set the variables of the BT
			Blackboard->SetValueAsObject(ExitPointKey, ExitPoint);
			Blackboard->SetValueAsBool(PossessMeatKey, bValue);
		}

		// Populate patrol point array (make an array with all point that are in the game)
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPatrolTargetPoint::StaticClass(), PatrolPoints);
	}		
}