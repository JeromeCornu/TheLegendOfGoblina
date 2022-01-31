// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUserWidgetclass.h"

void UInGameUserWidgetclass::NativeConstruct()
{
	if (SteaksBar)
	{
		SteaksBar->SetPercent(0.0);
	}
}