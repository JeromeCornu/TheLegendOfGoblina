// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GoblinaEatAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UGoblinaEatAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
    UGoblinaEatAnimNotify();

    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
