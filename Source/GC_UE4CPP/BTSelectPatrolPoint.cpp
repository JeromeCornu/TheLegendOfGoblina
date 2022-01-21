// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSelectPatrolPoint.h"
#include "AIPatrolTargetPoint.h"
#include "AIPatrolController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTSelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIPatrolController* AICon = Cast<AAIPatrolController>(OwnerComp.GetAIOwner());

	// Cast success ?
	if (AICon)
	{
		// Get BB component
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();

		AAIPatrolTargetPoint* CurrentPoint = Cast<AAIPatrolTargetPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

		TArray<AActor*> AvailablePatrolPoints = AICon->GetPatrolPoints();

		AAIPatrolTargetPoint* NextPatrolPoint = nullptr;

		
		// if there are more target points to go to
		if (AICon->CurrentPatrolPoint != AvailablePatrolPoints.Num() - 1)
		{
			NextPatrolPoint = Cast<AAIPatrolTargetPoint>(AvailablePatrolPoints[++AICon->CurrentPatrolPoint]); // -> go to the next point
		}
		// if there are no more target to go to 
		else
		{
			NextPatrolPoint = Cast<AAIPatrolTargetPoint>(AvailablePatrolPoints[0]); // -> return to the first point
			AICon->CurrentPatrolPoint = 0;
		}

		BlackboardComp->SetValueAsObject("LocationToGo", NextPatrolPoint);

		return EBTNodeResult::Succeeded;

	}

	return EBTNodeResult::Failed;
}
