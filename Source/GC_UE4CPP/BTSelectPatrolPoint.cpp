// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSelectPatrolPoint.h"
#include "AIPatrolTargetPoint.h"
#include "AIPatrolController.h"
#include "BehaviorTree/BlackboardComponent.h"

// One array with all points -> go to one of them randomly -> if (occupied) : repeat / else () : go to first point 
EBTNodeResult::Type UBTSelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

			// Get first point of the array of AAIPatrolTargetPoint
		AAIPatrolTargetPoint* FirstPoint = Cast<AAIPatrolTargetPoint>(AvailablePatrolPoints[0]);
			// Remove first point from the array
		AvailablePatrolPoints.Remove(FirstPoint);

		// Size of the array
		int32 ArrayLenght = AvailablePatrolPoints.Num();
		UE_LOG(LogTemp, Warning, TEXT("%d"), ArrayLenght);


		// if the place is occuiped by an aliment
		if (Occupied == true || FirstTime == true)
		{
			AICon->CurrentPatrolPoint = rand() % ArrayLenght - 1;
			NextPatrolPoint = Cast<AAIPatrolTargetPoint>(AvailablePatrolPoints[++AICon->CurrentPatrolPoint]); // -> go to the next random point
			FirstTime = false;
		}
		// if the place is free
		else
		{
			// Put the aliment
			NextPatrolPoint = FirstPoint; // -> return to the first point
			AICon->CurrentPatrolPoint = 0; // current point = the first
		}

		BlackboardComp->SetValueAsObject("LocationToGo", NextPatrolPoint); // link the BB's value with the variable NextPatrolPoint

		return EBTNodeResult::Succeeded;

	}

	return EBTNodeResult::Failed;
}
