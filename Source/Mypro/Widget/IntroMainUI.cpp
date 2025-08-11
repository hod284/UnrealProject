// Fill out your copyright notice in the Description page of Project Settings.


#include "IntroMainUI.h"

void UIntroMainUI::SetSwitcherIndex(int32 Index)
{
	if (Switcher)
	{
		Switcher->SetActiveWidgetIndex(Index);
	}

	laodingtitle->SetVisibility(Index==2? ESlateVisibility::Visible: ESlateVisibility::Collapsed);
	percenttext->SetVisibility(Index == 2 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UIntroMainUI::SetPercenttext(float pe)
{
	float va = pe * 100.0f;
	percenttext->SetText(FText::FromString(FString::Printf(TEXT("%d"), FMath::RoundToInt(va))));
}

void UIntroMainUI::NativeConstruct()
{
	Super::NativePreConstruct();
	laodingtitle = Cast<UTextBlock>(GetWidgetFromName(TEXT("loadingtitle")));
	percenttext = Cast<UTextBlock>(GetWidgetFromName(TEXT("percent")));
}

void UIntroMainUI::NativeDestruct()
{
	Super::NativeDestruct();

}
