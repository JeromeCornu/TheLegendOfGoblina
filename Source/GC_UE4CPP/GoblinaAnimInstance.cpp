// Fill out your copyright notice in the Description page of Project Settings.


#include "GoblinaAnimInstance.h"
#include "Goblina.h"
#include "ObjectiveItem.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Animations of the characters
UGoblinaAnimInstance::UGoblinaAnimInstance()
{
	// Initialisation of the variables
	bEatRef = false;

}

void UGoblinaAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// Reference to Goblina
	GoblinaReference = Cast<AGoblina>(TryGetPawnOwner());
}

void UGoblinaAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (GoblinaReference)
	{
		UpdateAnimProperties();
	}

	// Get the owning Actors
	else
	{
		AActor* Character = GetOwningActor();
		GoblinaReference = Cast<AGoblina>(Character);

		if (GoblinaReference)
		{
			UpdateAnimProperties();
		}
	}
}

// Here, variables are uptaded 
void UGoblinaAnimInstance::UpdateAnimProperties()
{

}

