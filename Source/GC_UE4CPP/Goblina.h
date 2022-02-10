// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Goblina.generated.h"

UCLASS()
class GC_UE4CPP_API AGoblina : public ACharacter
{
	GENERATED_BODY()

public:
	AGoblina( const FObjectInitializer& ObjectInitializer );

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		class UWidgetComponent* WidgetComp;

		class UGoblinaAnimInstance* GoblinaAnimRef;

	UFUNCTION()
		void StartEatAnimation();

	UFUNCTION()
		void StopEatAnimation();

};
