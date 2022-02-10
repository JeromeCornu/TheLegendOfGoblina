// Fill out your copyright notice in the Description page of Project Settings.


#include "CharactersAnimInstance.h"
#include "BaseCharacter.h"
#include "AIPatrol.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "GC_UE4CPPGameModeBase.h"

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
	GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
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
	
	//Test actor reference
	if (ActorReference)
	{

		//Test Speed  
		SpeedRef = ActorReference->GetVelocity().Size();

		if (ActorReference->bCarry)
		{
			bCarryRef = true;
		}

		else
		{
			bCarryRef = false;
		}

		if(ActorReference->bDead)
		{
			bFinishRef = true;
			bVictoryRef = true;
		}
		else if (GameMode->bFinish)
		{
			bFinishRef = true;
			bVictoryRef = false;
		}
	}
}
