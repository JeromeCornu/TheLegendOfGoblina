// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharactersAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UCharactersAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UCharactersAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// References to our characters
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
		class APlayableCharacter* PlayerReference;
	/*
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
		class AAIPatrol* AIReference;
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
		float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
		float bVictory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
		float bDefeat;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
		float bGrab;

	UFUNCTION(BlueprintCallable, Category = "Animations")
		virtual void UpdateAnimProperties();
};
