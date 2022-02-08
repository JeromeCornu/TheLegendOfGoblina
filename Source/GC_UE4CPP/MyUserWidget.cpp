// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GC_UE4CPPGameModeBase.h"


void UMyUserWidget::NativeConstruct()
{
	//corresponding button clicked to real function
	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UMyUserWidget::OnStartButtonClicked);
	}
	if (OptionsButton)
	{
		OptionsButton->OnClicked.AddDynamic(this, &UMyUserWidget::OnOptionsButtonClicked);
	}
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMyUserWidget::OnQuitButtonClicked);
	}
	
	
}

void UMyUserWidget::OnStartButtonClicked()
{
	UGameplayStatics::OpenLevel(this, "MainLevel", false);
}

void UMyUserWidget::OnOptionsButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("vous lancez les options"));
}

void UMyUserWidget::OnQuitButtonClicked()
{

	UE_LOG(LogTemp, Warning, TEXT("vous quittez l'application"));
	FPlatformMisc::RequestExit(false);
}
