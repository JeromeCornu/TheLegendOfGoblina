// Copyright Epic Games, Inc. All Rights Reserved.


#include "GC_UE4CPPGameModeBase.h"
#include "MyGameStateBase.h"

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