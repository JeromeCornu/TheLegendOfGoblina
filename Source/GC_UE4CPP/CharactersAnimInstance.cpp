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

	//Test de la reference joueur 
	if (PlayerReference)
	{

		//Test de vitesse 
		SpeedRef = PlayerReference->GetVelocity().Size();

		if (PlayerReference->bCarry)
		{
			bCarryRef = true;
		}

		else
		{
			bCarryRef = false;
		}

		if (PlayerReference->bDead)
		{
			bFinishRef = true;
			bVictoryRef = true;
		}
	}

	//Test de la reference de l'IA 
	if (AIReference)
	{
		//Test de vitesse 
		SpeedRefAI = AIReference->GetVelocity().Size();

		if (AIReference->bCarry)
		{
			bCarryRefAI = true;
		}
		
		else
		{
			bCarryRefAI = false;
		}

		if (AIReference->bDead)
		{
			bFinishRefAI = true;
			bVictoryRefAI = true;
		}
	}

}
