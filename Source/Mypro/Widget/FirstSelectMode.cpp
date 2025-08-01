// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstSelectMode.h"

void UFirstSelectMode::NativeConstruct()
{
	Super::NativeConstruct();
	// 싱글버튼 호버 이벤트 연결
	SingleButton->OnHovered.AddDynamic(this, &UFirstSelectMode::HoverSingleButton);
	// 싱글버튼 언호버 이벤트 연결
	SingleButton->OnUnhovered.AddDynamic(this, &UFirstSelectMode::UnHoverSingleButton);
	
	SingleButton->OnClicked.AddDynamic(this, &UFirstSelectMode::ClickSingleButton);
	// 멀티버튼 호버 이벤트 연결
	MultiButton->OnHovered.AddDynamic(this, &UFirstSelectMode::HoverMultiButton);
	// 멀티버튼 언호버 이벤트 연결
	MultiButton->OnUnhovered.AddDynamic(this, &UFirstSelectMode::UnHoverMultiButton);

	MultiButton->OnClicked.AddDynamic(this, &UFirstSelectMode::ClickMultiButton);
}

void UFirstSelectMode::HoverSingleButton()
{
	if(single)
		PlayAnimation(single,0.0,0,EUMGSequencePlayMode::Forward,1.0f);
}

void UFirstSelectMode::UnHoverSingleButton()
{
	if (single)
		StopAnimation(single);
}

void UFirstSelectMode::HoverMultiButton()
{
	if(multi)
		PlayAnimation(multi,0.0, 0, EUMGSequencePlayMode::Forward, 1.0f);
}

void UFirstSelectMode::UnHoverMultiButton()
{
	if (multi)
		StopAnimation(multi);
}

void UFirstSelectMode::ClickSingleButton()
{
	UIntroMainUI* ui = Cast<UIntroMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget());
	if (ui)
	{
		ui->SetSwitcherIndex(1);
	}
}

void UFirstSelectMode::ClickMultiButton()
{
	UIntroMainUI* ui = Cast<UIntroMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget());
	if (ui)
	{
		ui->SetSwitcherIndex(1);
	}
}


