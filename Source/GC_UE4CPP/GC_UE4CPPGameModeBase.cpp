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
	Player = Cast<APlayableCharacter>(PlayerController->GetPawn());
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
			UE_LOG(LogTemp, Warning, TEXT("Menu class was not defined"));
			return;
		}
		EndScreen = CreateWidget(GetWorld(), EndScreenClass);
		if (!EndScreen)
		{
			UE_LOG(LogTemp, Warning, TEXT("Menu Class was not defined"));
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
		UE_LOG(LogTemp, Warning, TEXT("c'est une victoire"));
		if (!EndScreenClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("end class was not defined"));
			return;
		}

	
		EndScreen = CreateWidget(GetWorld(), EndScreenClass);
		if (!EndScreen)
		{
			UE_LOG(LogTemp, Warning, TEXT("end Class was not defined"));
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



void AGC_UE4CPPGameModeBase::PauseGame()
{
	// if the game is not paused we create a widget 
	// if not we remove the widget
	if (!GameIsPaused)
	{
		if (!PauseScreenClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("Menu class was not defined"));
			return;
		}

		EndScreen = CreateWidget(GetWorld(), PauseScreenClass);

		if (!PauseScreen)
		{
			UE_LOG(LogTemp, Warning, TEXT("Menu Class was not defined"));
			return;
		}

		PauseScreen->AddToViewport();
		PauseScreen->SetVisibility(ESlateVisibility::Visible);

	UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
	else
	{
	PauseScreen->RemoveFromViewport();
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
}





