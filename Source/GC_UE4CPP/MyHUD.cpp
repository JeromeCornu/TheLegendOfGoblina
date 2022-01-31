// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

#include "Blueprint/UserWidget.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();
	if (!InGameHUDClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("hud class was not defined"));
		return;
	}


	InGameHUD = CreateWidget(GetWorld(), InGameHUDClass);

	if (!InGameHUD)
	{
		UE_LOG(LogTemp, Warning, TEXT("hud Class was not defined"));
		return;
	}

	InGameHUD->AddToViewport();
	InGameHUD->SetVisibility(ESlateVisibility::Visible);
}