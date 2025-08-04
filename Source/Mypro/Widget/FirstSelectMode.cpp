// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstSelectMode.h"

void UFirstSelectMode::NativeConstruct()
{
	Super::NativeConstruct();
	// 싱글버튼 호버 이벤트 연결
	SingleButton->OnHovered.AddDynamic(this, &UFirstSelectMode::HoverSingleButton);
	// 싱글버튼 언호버 이벤트 연결
	SingleButton->OnUnhovered.AddDynamic(this, &UFirstSelectMode::UnHoverSingleButton);
	// 싱글버튼 클릭 이벤트 연결
	SingleButton->OnClicked.AddDynamic(this, &UFirstSelectMode::ClickSingleButton);
	// 멀티버튼 호버 이벤트 연결
	MultiButton->OnHovered.AddDynamic(this, &UFirstSelectMode::HoverMultiButton);
	// 멀티버튼 언호버 이벤트 연결
	MultiButton->OnUnhovered.AddDynamic(this, &UFirstSelectMode::UnHoverMultiButton);
	// 멀티버튼 클릭 이벤트 연결
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
	// 싱글 버튼 호버 시 애니메이션 재생
	if(single)
		PlayAnimation(single,0.0,0,EUMGSequencePlayMode::Forward,1.0f);
}

void UFirstSelectMode::UnHoverSingleButton()
{
	// 싱글 버튼 언호버 시 애니메이션 정지
	if (single)
		StopAnimation(single);
}

void UFirstSelectMode::HoverMultiButton()
{
	// 멀티 버튼 호버 시 애니메이션 재생
	if(multi)
		PlayAnimation(multi,0.0, 0, EUMGSequencePlayMode::Forward, 1.0f);
}

void UFirstSelectMode::UnHoverMultiButton()
{
	// 멀티 버튼 언호버 시 애니메이션 정지
	if (multi)
		StopAnimation(multi);
}

void UFirstSelectMode::ClickSingleButton()
{
	// 싱글 버튼 클릭 시 IntroMainUI의 스위처 인덱스를 1로 설정하여 캐릭터 선택화면 으로 전환
	UIntroMainUI* ui = Cast<UIntroMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget());
	if (ui)
	{
		FirstSelectCharacter();
		ui->SetSwitcherIndex(1);
	}
}

void UFirstSelectMode::ClickMultiButton()
{
	// 멀티 버튼 클릭 시 IntroMainUI의 스위처 인덱스를 1로 설정하여 캐릭터 선택 화면으로 전환
	UIntroMainUI* ui = Cast<UIntroMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget());
	if (ui)
	{
		FirstSelectCharacter();
		ui->SetSwitcherIndex(1);
	}
}


