// Fill out your copyright notice in the Description page of Project Settings.


#include "CharactersAnimInstance.h"
#include "BaseCharacter.h"
#include "AIPatrol.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Animations of the characters
UCharactersAnimInstance::UCharactersAnimInstance()
{
	// Initialisation of the variables
	bVictoryRef = false;
	bFinishRef = false;
	bCarryRef = false;

	bVictoryRefAI = false;
	bFinishRefAI = false;
	bCarryRefAI = false;
}

void UCharactersAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	// Reference to the BaseCharacter
	PlayerReference = Cast<ABaseCharacter>(TryGetPawnOwner());
	AIReference = Cast<AAIPatrol>(TryGetPawnOwner());
}

void UCharactersAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	// Call the Update animations function of the player/AI
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (PlayerReference || AIReference)
	{
		UpdateAnimProperties();
	}
	
	// Get the owning Actors
	else
	{
		AActor* Character = GetOwningActor();
		AActor* CharacterAI = TryGetPawnOwner();
		PlayerReference = Cast<ABaseCharacter>(Character);
		AIReference = Cast<AAIPatrol>(CharacterAI);

		if (PlayerReference || AIReference)
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
	if (SpeedRefAI)
	{
		SpeedRefAI = AIReference->GetVelocity().Size();
	}

	// Test Carry a revoir 
	if (PlayerReference->bCarry)
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
