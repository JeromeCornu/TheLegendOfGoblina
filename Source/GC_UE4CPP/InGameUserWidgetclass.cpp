// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUserWidgetclass.h"



void UInGameUserWidgetclass::NativeConstruct()
{
	if (SteaksBar)
	{
		GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
		GameMode->SetSteaks(0);
		SteaksBar->SetPercent(GameMode->GetSteaks());
		
	}
}

void UInGameUserWidgetclass::SetPercentage(float Percent)
{
	if (SteaksBar !=NULL)
	{
	SteaksBar->SetPercent(Percent);
	}
}
