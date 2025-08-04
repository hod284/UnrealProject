// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstSelectMode.h"

void UFirstSelectMode::NativeConstruct()
{
	Super::NativeConstruct();
	// �̱۹�ư ȣ�� �̺�Ʈ ����
	SingleButton->OnHovered.AddDynamic(this, &UFirstSelectMode::HoverSingleButton);
	// �̱۹�ư ��ȣ�� �̺�Ʈ ����
	SingleButton->OnUnhovered.AddDynamic(this, &UFirstSelectMode::UnHoverSingleButton);
	// �̱۹�ư Ŭ�� �̺�Ʈ ����
	SingleButton->OnClicked.AddDynamic(this, &UFirstSelectMode::ClickSingleButton);
	// ��Ƽ��ư ȣ�� �̺�Ʈ ����
	MultiButton->OnHovered.AddDynamic(this, &UFirstSelectMode::HoverMultiButton);
	// ��Ƽ��ư ��ȣ�� �̺�Ʈ ����
	MultiButton->OnUnhovered.AddDynamic(this, &UFirstSelectMode::UnHoverMultiButton);
	// ��Ƽ��ư Ŭ�� �̺�Ʈ ����
	MultiButton->OnClicked.AddDynamic(this, &UFirstSelectMode::ClickMultiButton);
}

void UFirstSelectMode::FirstSelectCharacter()
{
	AMainPlayerController* controller = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	if (controller)
	{
		AIntroSceneObject* levelob = Cast<AIntroSceneObject>(controller->GetLevelSceneObjectActor());
		if (levelob)
		{
			levelob->CalltheSelectCharacter(CharacterChoice::Warrior);
		}
	}
}

void UFirstSelectMode::HoverSingleButton()
{
	// �̱� ��ư ȣ�� �� �ִϸ��̼� ���
	if(single)
		PlayAnimation(single,0.0,0,EUMGSequencePlayMode::Forward,1.0f);
}

void UFirstSelectMode::UnHoverSingleButton()
{
	// �̱� ��ư ��ȣ�� �� �ִϸ��̼� ����
	if (single)
		StopAnimation(single);
}

void UFirstSelectMode::HoverMultiButton()
{
	// ��Ƽ ��ư ȣ�� �� �ִϸ��̼� ���
	if(multi)
		PlayAnimation(multi,0.0, 0, EUMGSequencePlayMode::Forward, 1.0f);
}

void UFirstSelectMode::UnHoverMultiButton()
{
	// ��Ƽ ��ư ��ȣ�� �� �ִϸ��̼� ����
	if (multi)
		StopAnimation(multi);
}

void UFirstSelectMode::ClickSingleButton()
{
	// �̱� ��ư Ŭ�� �� IntroMainUI�� ����ó �ε����� 1�� �����Ͽ� ĳ���� ����ȭ�� ���� ��ȯ
	UIntroMainUI* ui = Cast<UIntroMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget());
	if (ui)
	{
		FirstSelectCharacter();
		ui->SetSwitcherIndex(1);
	}
}

void UFirstSelectMode::ClickMultiButton()
{
	// ��Ƽ ��ư Ŭ�� �� IntroMainUI�� ����ó �ε����� 1�� �����Ͽ� ĳ���� ���� ȭ������ ��ȯ
	UIntroMainUI* ui = Cast<UIntroMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget());
	if (ui)
	{
		FirstSelectCharacter();
		ui->SetSwitcherIndex(1);
	}
}


