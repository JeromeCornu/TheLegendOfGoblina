// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSaveSelectPatrolPoint.h"
#include "AIPatrolTargetPoint.h"
#include "AIPatrolController.h"
#include "BehaviorTree/BlackboardComponent.h"

// Road to follow
EBTNodeResult::Type UBTSaveSelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIPatrolController* AICon = Cast<AAIPatrolController>(OwnerComp.GetAIOwner());

	// Cast success ?
	if (AICon)
	{
		// Get BB component
			// Variable of the BB
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
			// Point where the AI is
		AAIPatrolTargetPoint* CurrentPoint = Cast<AAIPatrolTargetPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));
			// Other points
		TArray<AActor*> AvailablePatrolPoints = AICon->GetPatrolPoints();
			// Next point
		AAIPatrolTargetPoint* NextPatrolPoint = nullptr;


		// if there are more target points to go to
		if (AICon->CurrentPatrolPoint != AvailablePatrolPoints.Num() - 1)
		{
			NextPatrolPoint = Cast<AAIPatrolTargetPoint>(AvailablePatrolPoints[++AICon->CurrentPatrolPoint]); // -> go to the next point
		}
		// if there are no more target points to go to 
		else
		{
			NextPatrolPoint = Cast<AAIPatrolTargetPoint>(AvailablePatrolPoints[0]); // -> return to the first point
			AICon->CurrentPatrolPoint = 0; // current point = the first
		}

		BlackboardComp->SetValueAsObject("LocationToGo", NextPatrolPoint); // link the BB's value with the variable NextPatrolPoint

		return EBTNodeResult::Succeeded;

	}

	return EBTNodeResult::Failed;
}
