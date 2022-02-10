// Copyright Epic Games, Inc. All Rights Reserved.


#include "GC_UE4CPPGameModeBase.h"
#include "MyGameStateBase.h"
#include "EndScreen.h"
#include "Blueprint/UserWidget.h"
#include "InGameUserWidgetClass.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacterController.h"
#include "AIPatrol.h"
#include "BaseCharacter.h"
#include "PlayableCharacter.h"
#include "Kismet/GameplayStatics.h"


AGC_UE4CPPGameModeBase::AGC_UE4CPPGameModeBase()
{
	GameStateClass = AMyGameStateBase::StaticClass();
}

void AGC_UE4CPPGameModeBase::BeginPlay()
{
	
	PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		Player = Cast<APlayableCharacter>(PlayerController->GetPawn());
	}

	bVictory = false;
	bFinish = false;
	
}

float AGC_UE4CPPGameModeBase::GetSteaks() const
{
	return GetGameState<AMyGameStateBase>()->NumberOfSteaks;
}

void AGC_UE4CPPGameModeBase::SetSteaks(float newSteaks)
{
	GetGameState<AMyGameStateBase>()->NumberOfSteaks = newSteaks;
}

float AGC_UE4CPPGameModeBase::GetSteaksInGame() const
{
	return GetGameState<AMyGameStateBase>()->NumberOfSteaksInGame;
}


void AGC_UE4CPPGameModeBase::SetSteaksInGame(float newSteaks)
{
	GetGameState<AMyGameStateBase>()->NumberOfSteaksInGame = newSteaks;
}


void AGC_UE4CPPGameModeBase::Lose()
{
	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);
	if (!bFinish) 
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPatrol::StaticClass(), Actors);
		for (int i = 0; i < Actors.Num(); i++)
		{
			AAIPatrol* Patrol = Cast<AAIPatrol>(Actors[i]);
			if (Patrol) 
			{
				Patrol->AIEnd();
			}
		}
		bFinish = true;
		InGameHUD = Cast<UInGameUserWidgetclass>(PlayerController->InGameHUD);
		if (Player)
		{
			Player->PlayerEnd();
		}
	
		bVictory = false;
	
		if (!EndScreenClass)
		{
			return;
		}
		EndScreen = CreateWidget(GetWorld(), EndScreenClass);
		if (!EndScreen)
		{
			return;
		}
		InGameHUD->RemoveFromViewport();

		EndScreen->AddToViewport();
		EndScreen->SetVisibility(ESlateVisibility::Visible);
		UserWidgetEndScreen = Cast<UEndScreen>(this->EndScreen);
		UserWidgetEndScreen->Lose();

		PlayerController->UnPossess();
	}
}

void AGC_UE4CPPGameModeBase::Victory()
{
	if (!bFinish) 
	{
		bVictory = true;
		bFinish = true;
		if (Player)
		{
			Player->PlayerEnd();
		}
		if (!EndScreenClass)
		{
			return;
		}

	
		EndScreen = CreateWidget(GetWorld(), EndScreenClass);
		if (!EndScreen)
		{
			return;
		}
		InGameHUD->RemoveFromViewport();

		EndScreen->AddToViewport();
		EndScreen->SetVisibility(ESlateVisibility::Visible);
		UserWidgetEndScreen = Cast<UEndScreen>(this->EndScreen);
		UserWidgetEndScreen->Win();

		PlayerController->UnPossess();
	}
	
}

//when the player take a steak update the UI
void AGC_UE4CPPGameModeBase::GetaSteak()
{
	
	float Temp = GetSteaks();
	Temp = Temp +0.2F;
	SetSteaks(Temp);
	
	InGameHUD = Cast<UInGameUserWidgetclass>(PlayerController->InGameHUD);
	if (InGameHUD)
	{
		InGameHUD->SetPercentage(GetSteaks());
	}
	if (Temp >= 1)
	{
		Victory();
	}
}


float AGC_UE4CPPGameModeBase::GetAI()
{
	return GetGameState<AMyGameStateBase>()->NumberOfAI;
}

void AGC_UE4CPPGameModeBase::SetAI(float AI)
{
	GetGameState<AMyGameStateBase>()->NumberOfAI = AI;
}









