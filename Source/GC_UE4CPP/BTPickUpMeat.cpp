// Fill out your copyright notice in the Description page of Project Settings.


#include "BTPickUpMeat.h"
#include "AIPatrolController.h"
#include "BaseCharacter.h"
#include "ObjectiveItem.h"
#include "BehaviorTree/BlackboardComponent.h"

// One array with all points -> go to one of them randomly -> if (occupied) : repeat / else () : go to first point 
EBTNodeResult::Type UBTPickUpMeat::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIPatrolController* AICon = Cast<AAIPatrolController>(OwnerComp.GetAIOwner());
	ABaseCharacter* AICharacter = Cast<ABaseCharacter>(AICon->GetCharacter());

	// Cast success ?
	if (AICon)
	{
		if (AICharacter)
		{
			// Variable of the BB
			UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();

			// Call the function Interact() to pick or drop the object
			AICharacter->Interact();


			if (AICharacter->PossessedObject)
			{
				bPossessMeatOrNot = true;
			}
			else
			{
				bPossessMeatOrNot = false;
			}

			BlackboardComp->SetValueAsBool("PossessMeat", bPossessMeatOrNot); // link the BB's value with the variable PossessMeat

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}

void UBTPickUpMeat::SetPossessMeat(bool value)
{
	bPossessMeatOrNot = value;
}