// Fill out your copyright notice in the Description page of Project Settings.


#include "BTInteract.h"

#include "GC_UE4CPP/BaseCharacter.h"
#include "GC_UE4CPP/AIPatrolController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTInteract::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABaseCharacter* Character = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetCharacter());


	if (Character)
	{
		Character->Interact();

		if (Character->PossessedObject)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(KeyForPossessFoodBool, true);
		}
		else {
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(KeyForPossessFoodBool, false);
		}

		if (bDropFoodLocationRefNeeded) 
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(KeyForFoodLocation, Character->GetActorLocation());
		}

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}