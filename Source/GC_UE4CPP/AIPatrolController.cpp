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
	// AAIPatrol* AICharacter = (AAIPatrol*)InPawn;
	AAIPatrol* AICharacter = Cast<AAIPatrol>(InPawn);
	ASpawnVolume* ExitPoint = AICharacter->Spawner;

	if (AICharacter)
	{
		// Set the variable ExitPoint of the BT as the spawner
		Blackboard->SetValueAsObject("ExitPoint", ExitPoint);     // ICI CA CRASH
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("First point registered"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("HELP ca a crash"));
	}

	// Cast succesful ?
	if (AICharacter) 
	{
		RunBehaviorTree(AICharacter->BehaviorTree);

		// Initialize the BehaviorTree's value : PossessMeat
		bool bValue = true;
		Blackboard->SetValueAsBool("PossessMeat", bValue);


		// Populate patrol point array (make an array with all point that are in the game)
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPatrolTargetPoint::StaticClass(), PatrolPoints);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("PossessMeat"));
	}
}