// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDestroyOwner.h"


#include "GC_UE4CPP/AIPatrol.h"
#include "GC_UE4CPP/AIPatrolController.h"
#include "GC_UE4CPP/GC_UE4CPPGameModeBase.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTDestroyOwner::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIPatrol* Character = Cast<AAIPatrol>(OwnerComp.GetAIOwner()->GetCharacter());
	AGC_UE4CPPGameModeBase* GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());

	if (Character) 
	{
		Character->Despawn();

		GameMode->DelegateDestroy.Broadcast();
	}

	return EBTNodeResult::Failed;
}