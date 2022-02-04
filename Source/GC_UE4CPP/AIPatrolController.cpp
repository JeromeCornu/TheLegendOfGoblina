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
	// Initialize blackboard abnd behavior tree
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	// Initialize blackboard keys
	PlayerKey = "Player";
	LocationToGoKey = "LocationToGo";

	CurrentPatrolPoint = 0;
}

void AAIPatrolController::BeginPlay()
{
	Super::BeginPlay();

	// Initialize the BehaviorTree's value : PossessMeat
	bool bValue = true;
	BlackboardComp->SetValueAsBool("PossessMeat", bValue);
}

// The player has been see -> set a key on the blackboard
void AAIPatrolController::SetPlayerCaught(APawn* _Pawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(PlayerKey, _Pawn);
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
		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
		}

		// Populate patrol point array (make an array with all point that are in the game)
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPatrolTargetPoint::StaticClass(), PatrolPoints);
		
		BehaviorComp->StartTree(*AICharacter->BehaviorTree);

	}
}