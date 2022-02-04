// Fill out your copyright notice in the Description page of Project Settings.


#include "CharactersAnimInstance.h"
#include "BaseCharacter.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Animations of the characters
UCharactersAnimInstance::UCharactersAnimInstance()
{
	// Initialisation of the variables
	bVictoryRef = false;
	bFinishRef = false;
	bCarryRef = false;
}

void UCharactersAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	// Reference to the BaseCharacter
	PlayerReference = Cast<ABaseCharacter>(TryGetPawnOwner());
}

void UCharactersAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	// Call the Update animations function of the player
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (PlayerReference)
	{
		UpdateAnimProperties();
	}
	// Get the owning Actors
	else
	{
		AActor* Character = GetOwningActor();
		PlayerReference = Cast<ABaseCharacter>(Character);

		if (PlayerReference)
		{
			UpdateAnimProperties();
		}
	}
}

// Here, variables are uptaded 
void UCharactersAnimInstance::UpdateAnimProperties()
{
	// Test Speed
	SpeedRef = PlayerReference->GetVelocity().Size();

	// Test Carry
	if (PlayerReference)
	{
		bCarryRef = true;
	}
	else
	{
		bCarryRef = false;
	}

	// Test End
	if (PlayerReference->bDead)
	{
		bFinishRef = true;
		bVictoryRef = true;
	}
}
