// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSelectRandomPoint.h"
#include "AIPatrolTargetPoint.h"
#include "AIPatrolController.h"
#include "BehaviorTree/BlackboardComponent.h"

// One array with all points -> go to one of them randomly -> if (occupied) : repeat / else () : go to first point 
EBTNodeResult::Type UBTSelectRandomPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIPatrolController* AICon = Cast<AAIPatrolController>(OwnerComp.GetAIOwner());

	// Cast success ?
	if (AICon)
	{
		// Get BB component
			// Point where the AI is
		AAIPatrolTargetPoint* CurrentPoint = Cast<AAIPatrolTargetPoint>(AICon->GetBlackboardComp()->GetValueAsObject("RandomPoint"));
			// Other points
		TArray<AActor*> AllPoints = AICon->GetAllPoints();
			// Next point
		AAIPatrolTargetPoint* NextPatrolPoint = nullptr;


		// Size of the array
		int32 ArrayLenght = AllPoints.Num();


		// if the place is occuiped by an aliment
		AICon->CurrentPatrolPoint = rand() % ArrayLenght - 1;
		NextPatrolPoint = Cast<AAIPatrolTargetPoint>(AllPoints[++AICon->CurrentPatrolPoint]); // -> go to the next random point


		AICon->GetBlackboardComp()->SetValueAsObject("RandomPoint", NextPatrolPoint); // link the BB's value with the variable NextPatrolPoint

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("HERE"));

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

