// Fill out your copyright notice in the Description page of Project Settings.


#include "IntroMainUI.h"

void UIntroMainUI::SetSwitcherIndex(int32 Index)
{
	if (Switcher)
	{
		Switcher->SetActiveWidgetIndex(Index);
	}

}

void UIntroMainUI::NativeConstruct()
{
	Super::NativePreConstruct();

}

void UIntroMainUI::NativeDestruct()
{
	Super::NativeDestruct();

}
