// Fill out your copyright notice in the Description page of Project Settings.


#include "CharactersAnimInstance.h"
#include "PlayableCharacter.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

UCharactersAnimInstance::UCharactersAnimInstance()
{
	// Initialisation of the variables
	bVictoryRef = false;
	bFinishRef = false;
	bCarryRef = false;
	//Speed = 0.0f;
}

void UCharactersAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	// Faire plutot une ref au BasePlayerCharacter
	PlayerReference = Cast<APlayableCharacter>(TryGetPawnOwner());
	//AIReference = Cast<AAIPatrol>(TryGetPawnOwner());
}

void UCharactersAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	// Call the Update animations function of the player
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (PlayerReference)
	{
		UpdateAnimProperties();
	}
	// Get all Actors of the PlayableCharacters Class
	// Not useful for the player character
	else
	{
		AActor* Character = GetOwningActor();
		PlayerReference = Cast<APlayableCharacter>(Character);

		if (PlayerReference)
		{
			UpdateAnimProperties();
		}
		//TArray<AActor*> OutActors;
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayableCharacter::StaticClass(), OutActors); // GetOwningActor
		
		/*
		for (AActor* Actor : OutActors)
		{
			PlayerReference = Cast<APlayableCharacter>(Actor);
			if (PlayerReference)
			{
				UpdateAnimProperties();
				break;
			}
		}
		*/
	}
}

// Here, variables are uptaded 
void UCharactersAnimInstance::UpdateAnimProperties()
{
	SpeedRef = PlayerReference->GetVelocity().Size();
	//bCarryRef = PlayerReference
	// bVictory = PlayerReference->IsItAWin();
	// bDefeat = PlayerReference->IsItALoose();
}
