#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));

	if (!ExampleUIClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("ExampleUIClass was not defined"));
		return;
	}


	ExampleUI = CreateWidget(this, ExampleUIClass);

	if (!ExampleUI)
	{
		UE_LOG(LogTemp, Warning, TEXT("ExampleUI was not defined"));
		return;
	}

	ExampleUI->AddToViewport();
	ExampleUI->SetVisibility(ESlateVisibility::Visible);
}