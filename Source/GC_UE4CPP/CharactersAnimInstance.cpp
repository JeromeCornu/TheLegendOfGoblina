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

}

void UCharactersAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// Reference to the BaseCharacter
	ActorReference = Cast<ABaseCharacter>(TryGetPawnOwner());
}

void UCharactersAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	// Call the Update animations function of the player/AI
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (ActorReference) 
	{
		UpdateAnimProperties();
	}
	
	// Get the owning Actors
	else
	{
		AActor* Character = GetOwningActor();
		ActorReference = Cast<ABaseCharacter>(Character);
		
		if (ActorReference )
		{
			UpdateAnimProperties();
		}
	}
}

// Here, variables are uptaded 
void UCharactersAnimInstance::UpdateAnimProperties()
{

	//Test de la reference joueur 
	if (ActorReference)
	{

		//Test de vitesse 
		SpeedRef = ActorReference->GetVelocity().Size();

		if (ActorReference->bCarry)
		{
			bCarryRef = true;
		}

		else
		{
			bCarryRef = false;
		}

		if (ActorReference->bDead)
		{
			bFinishRef = true;
			bVictoryRef = true;
		}
	}
}
