// Copyright Epic Games, Inc. All Rights Reserved.


#include "GC_UE4CPPGameModeBase.h"
#include "MyGameStateBase.h"
#include "Blueprint/UserWidget.h"

AGC_UE4CPPGameModeBase::AGC_UE4CPPGameModeBase()
{
	GameStateClass = AMyGameStateBase::StaticClass();
}
int32 AGC_UE4CPPGameModeBase::GetSteaks() const
{
	return GetGameState<AMyGameStateBase>()->NumberOfSteaks;
}
void AGC_UE4CPPGameModeBase::SetSteaks(int32 newSteaks)
{
	GetGameState<AMyGameStateBase>()->NumberOfSteaks = newSteaks;
}
void AGC_UE4CPPGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));

	if (!ExampleUIClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("ExampleUIClass was not defined"));
		return;
	}

	
	ExampleUI = CreateWidget(GetWorld(), ExampleUIClass);

	if (!ExampleUI)
	{
		UE_LOG(LogTemp, Warning, TEXT("ExampleUI was not defined"));
		return;
	}

	ExampleUI->AddToViewport();
	ExampleUI->SetVisibility(ESlateVisibility::Visible);
}