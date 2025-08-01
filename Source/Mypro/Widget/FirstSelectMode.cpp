// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstSelectMode.h"

void UFirstSelectMode::NativeConstruct()
{
	Super::NativeConstruct();
	// �̱۹�ư ȣ�� �̺�Ʈ ����
	SingleButton->OnHovered.AddDynamic(this, &UFirstSelectMode::HoverSingleButton);
	// �̱۹�ư ��ȣ�� �̺�Ʈ ����
	SingleButton->OnUnhovered.AddDynamic(this, &UFirstSelectMode::UnHoverSingleButton);
	
	SingleButton->OnClicked.AddDynamic(this, &UFirstSelectMode::ClickSingleButton);
	// ��Ƽ��ư ȣ�� �̺�Ʈ ����
	MultiButton->OnHovered.AddDynamic(this, &UFirstSelectMode::HoverMultiButton);
	// ��Ƽ��ư ��ȣ�� �̺�Ʈ ����
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


