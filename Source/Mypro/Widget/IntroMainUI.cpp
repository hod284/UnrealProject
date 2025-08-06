// Fill out your copyright notice in the Description page of Project Settings.


#include "IntroMainUI.h"

void UIntroMainUI::SetSwitcherIndex(int32 Index)
{
	if (Switcher)
	{
		Switcher->SetActiveWidgetIndex(Index);
	}
	else
	UE_LOG(LogMypro, Warning, TEXT("Switcher is null!"));
	
}

void UIntroMainUI::NativeConstruct()
{
	Super::NativePreConstruct();

	UE_LOG(LogMypro, Warning, TEXT("NativePreConstruct"));
}

void UIntroMainUI::NativeDestruct()
{
	Super::NativeDestruct();
	UE_LOG(LogMypro, Warning, TEXT("NativeDestruct"));
}
