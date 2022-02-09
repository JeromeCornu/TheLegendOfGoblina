// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTryThisPlate.h"


#include "GC_UE4CPP/StandItem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTryThisPlate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AStandItem* Plate = Cast<AStandItem>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(PlateKey));

	if (Plate)
	{
		if (!Plate->LaidItem) 
		{
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
