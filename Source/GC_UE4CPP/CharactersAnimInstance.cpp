// Fill out your copyright notice in the Description page of Project Settings.


#include "CharactersAnimInstance.h"
#include "PlayableCharacter.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

UCharactersAnimInstance::UCharactersAnimInstance()
{
	// Initialisation of the variables
	bVictory = false;
	bDefeat = false;
	bGrab = false;
}

void UCharactersAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
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
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayableCharacter::StaticClass(), OutActors);

		for (AActor* Actor : OutActors)
		{
			PlayerReference = Cast<APlayableCharacter>(Actor);
			if (PlayerReference)
			{
				UpdateAnimProperties();
				break;
			}
		}
	}
}

// Here, variables are uptaded 
void UCharactersAnimInstance::UpdateAnimProperties()
{
	Speed = PlayerReference->GetVelocity().Size();
	// bVictory = PlayerReference->IsItAWin();
	// bDefeat = PlayerReference->IsItALoose();
}
