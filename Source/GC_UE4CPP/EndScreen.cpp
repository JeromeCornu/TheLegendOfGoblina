
#include "EndScreen.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

#include "GC_UE4CPPGameModeBase.h"




void UEndScreen::NativeConstruct()
{
	//corresponding button clicked to real function
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UEndScreen::OnRestartButtonClicked);
	}
	if (BackToMenuButton)
	{
		BackToMenuButton->OnClicked.AddDynamic(this, &UEndScreen::OnBackToMenuButtonClicked);
	}
	if (VictoryDefeatText)
	{
		VictoryDefeatText = Cast<UTextBlock>(GetWidgetFromName("VictoryDefeatText"));
	}
	if (GameMode)
	{
		GameMode = Cast<AGC_UE4CPPGameModeBase>(GetWorld()->GetAuthGameMode());
	}
	
	
}

void UEndScreen::OnRestartButtonClicked()
{
	UGameplayStatics::OpenLevel(this, "MainLevel", false);
}

void UEndScreen::OnBackToMenuButtonClicked()
{
	UGameplayStatics::OpenLevel(this, "MainMenu", false);
}

void UEndScreen::Lose()
{
	VictoryDefeatText->SetColorAndOpacity( FSlateColor(FLinearColor::Red));
	VictoryDefeatText->SetText(FText::FromString("YOU LOST"));
	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);
	
}

void UEndScreen::Win()
{
	VictoryDefeatText->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
	VictoryDefeatText->SetText(FText::FromString("YOU WON"));
	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);

}