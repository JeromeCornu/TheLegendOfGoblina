// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSelectRandomPlate.h"


#include "GC_UE4CPP/AIPatrolController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTSelectRandomPlate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIPatrolController* Controller = Cast<AAIPatrolController>(OwnerComp.GetAIOwner());

	if (Controller)
	{
		int32 RandIndex = FMath::RandRange(0, Controller->GetPlatesArray().Num() - 1);

		if (RandIndex == Controller->PlateIndex)
		{
			return EBTNodeResult::Failed;
		}

		Controller->PlateIndex = RandIndex;
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(Key, Controller->GetPlatesArray()[RandIndex]);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

