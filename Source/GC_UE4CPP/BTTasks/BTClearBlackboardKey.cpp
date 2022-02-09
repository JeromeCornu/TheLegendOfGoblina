// Fill out your copyright notice in the Description page of Project Settings.


#include "BTClearBlackboardKey.h"

#include "GC_UE4CPP/AIPatrolController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTClearBlackboardKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->ClearValue(Key);

	if (Key != "None")
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(Key);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}