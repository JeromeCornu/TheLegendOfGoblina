// Fill out your copyright notice in the Description page of Project Settings.


#include "BTPickUpMeat.h"
#include "AIPatrolController.h"
#include "BehaviorTree/BlackboardComponent.h"

// One array with all points -> go to one of them randomly -> if (occupied) : repeat / else () : go to first point 
EBTNodeResult::Type UBTPickUpMeat::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIPatrolController* AICon = Cast<AAIPatrolController>(OwnerComp.GetAIOwner());

	// Cast success ?
	if (AICon)
	{
		// Get BB component
			// Variable of the BB
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();


		BlackboardComp->SetValueAsBool("PossessMeat", true); // link the BB's value with the variable NextPatrolPoint


		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
