// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTSelectRandomPoint.generated.h"

/**
 *
 */
UCLASS()
class GC_UE4CPP_API UBTSelectRandomPoint : public UBTTaskNode
{
	GENERATED_BODY()

		// EBTNodeResult -> like boolean but with other possibilities of return (like : succeeded, failed)
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
