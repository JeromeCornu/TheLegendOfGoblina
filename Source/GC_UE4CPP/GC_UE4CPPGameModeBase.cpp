// Copyright Epic Games, Inc. All Rights Reserved.


#include "GC_UE4CPPGameModeBase.h"
#include "MyGameStateBase.h"
#include "EndScreen.h"
#include "Blueprint/UserWidget.h"
#include "InGameUserWidgetClass.h"



//constructeur et definition du game state
AGC_UE4CPPGameModeBase::AGC_UE4CPPGameModeBase()
{
	GameStateClass = AMyGameStateBase::StaticClass();
	//InGameHUD = Cast<UInGameUserWidgetclass>();
	
}

//getter des steaks récuperé par le joueur
int32 AGC_UE4CPPGameModeBase::GetSteaks() const
{
	return GetGameState<AMyGameStateBase>()->NumberOfSteaks;
}

//setter des steaks récuperé par le joueur
void AGC_UE4CPPGameModeBase::SetSteaks(int32 newSteaks)
{
	GetGameState<AMyGameStateBase>()->NumberOfSteaks = newSteaks;
}

void AGC_UE4CPPGameModeBase::Lose()
{
	if (!EndScreenClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Menu class was not defined"));
		return;
	}
	EndScreen = CreateWidget(GetWorld(), EndScreenClass);
	if (!EndScreen)
	{
		UE_LOG(LogTemp, Warning, TEXT("Menu Class was not defined"));
		return;
	}

	EndScreen->AddToViewport();
	EndScreen->SetVisibility(ESlateVisibility::Visible);
	
}

void AGC_UE4CPPGameModeBase::Victory()
{
	if (!EndScreenClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Menu class was not defined"));
		return;
	}

	
	EndScreen = CreateWidget(GetWorld(), EndScreenClass);
	if (!EndScreen)
	{
		UE_LOG(LogTemp, Warning, TEXT("Menu Class was not defined"));
		return;
	}

	EndScreen->AddToViewport();
	EndScreen->SetVisibility(ESlateVisibility::Visible);
	
}

void AGC_UE4CPPGameModeBase::GetaSteak()
{
	int32 Temp = GetSteaks();
	Temp += 1;
	SetSteaks(Temp);
	InGameHUD->SetPercentage(GetSteaks());
}


