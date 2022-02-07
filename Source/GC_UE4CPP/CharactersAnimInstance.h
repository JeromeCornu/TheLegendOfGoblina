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
		class ABaseCharacter* ActorReference;
	

//Animation variable targeting all characters

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
		float SpeedRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
		bool bVictoryRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
		bool bFinishRef;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
		bool bCarryRef;


	UFUNCTION(BlueprintCallable, Category = "Animations")
		virtual void UpdateAnimProperties();
};
