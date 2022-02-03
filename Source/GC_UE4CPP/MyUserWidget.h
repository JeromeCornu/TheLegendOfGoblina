// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GC_UE4CPPGameModeBase.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UMyUserWidget : public UUserWidget
{

	GENERATED_BODY()

public:

		
	class AGC_UE4CPPGameModeBase* GameMode;
	
	
	
protected:
	

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* StartButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* OptionsButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* QuitButton;

	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnStartButtonClicked();

	UFUNCTION()
		void OnOptionsButtonClicked();

	UFUNCTION()
		void OnQuitButtonClicked();

	    
};
