// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GoblinaAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UGoblinaAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	UGoblinaAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// References to our characters
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
		class AGoblina* GoblinaReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
		class AObjectiveItem* ObjectiveReference;

	UFUNCTION(BlueprintCallable, Category = "Animations")
		virtual void UpdateAnimProperties();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
		bool bEatRef;

};
