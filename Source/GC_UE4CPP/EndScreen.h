// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "EndScreen.generated.h"


/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UEndScreen : public UUserWidget
{
	GENERATED_BODY()

	class AGC_UE4CPPGameModeBase* GameMode;
	FName VictoryDefeatTextBlockName;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* VictoryDefeatText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* RestartButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* BackToMenuButton;

	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnRestartButtonClicked();

	UFUNCTION()
		void OnBackToMenuButtonClicked();
public:	
	

	UFUNCTION()
		void Lose();

	UFUNCTION()
		void Win();
	
};
