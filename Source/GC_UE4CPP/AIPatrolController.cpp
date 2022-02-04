// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPatrolController.h"
#include "AIPatrol.h"
#include "AIPatrolTargetPoint.h"
#include "BTPickUpMeat.h"
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
	AAIPatrol* AICharacter = (AAIPatrol*)InPawn;

	// Cast succesful ?
	if (AICharacter) 
	{
		RunBehaviorTree(AICharacter->BehaviorTree);

		// Initialize the BehaviorTree's value : PossessMeat
		bool bValue = true;
		Blackboard->SetValueAsBool("PossessMeat", bValue);



		// Populate patrol point array (make an array with all point that are in the game)
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPatrolTargetPoint::StaticClass(), PatrolPoints);



		GetAllPoints();



		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("PossessMeat"));
	}
}

TArray<AActor*> AAIPatrolController::GetAllPoints()
{
	// Get all points available
	TArray<AActor*> AvailablePatrolPoints = GetPatrolPoints();

	// Get first point of the array : AAIPatrolTargetPoint, remove it and set it as the ExitPoint
	AAIPatrolTargetPoint* ExitPoint = Cast<AAIPatrolTargetPoint>(AvailablePatrolPoints[0]);
	// Remove first point from the array
	AvailablePatrolPoints.Remove(ExitPoint);
	// Set the variable FirstPoint of the BT
	Blackboard->SetValueAsObject("ExitPoint", ExitPoint);

	return AvailablePatrolPoints;
}