// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDestroyOwner.h"


#include "GC_UE4CPP/AIPatrol.h"
#include "GC_UE4CPP/AIPatrolController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTDestroyOwner::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIPatrol* Character = Cast<AAIPatrol>(OwnerComp.GetAIOwner()->GetCharacter());

	if (Character) 
	{
		Character->Despawn();
	}

	return EBTNodeResult::Failed;
}