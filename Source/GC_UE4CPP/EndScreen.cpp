// Fill out your copyright notice in the Description page of Project Settings.


#include "EndScreen.h"
#include "Blueprint/UserWidget.h"

void AEndScreen::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));

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