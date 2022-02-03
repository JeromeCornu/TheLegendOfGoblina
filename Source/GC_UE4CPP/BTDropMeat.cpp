// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDropMeat.h"
#include "AIPatrolController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTDropMeat::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIPatrolController* AICon = Cast<AAIPatrolController>(OwnerComp.GetAIOwner());

	// Cast success ?
	if (AICon)
	{
		// Get BB component
			// Variable of the BB
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();


		BlackboardComp->SetValueAsBool("PossessMeat", false); // link the BB's value with the variable NextPatrolPoint


		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}