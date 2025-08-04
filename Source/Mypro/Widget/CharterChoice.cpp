// Fill out your copyright notice in the Description page of Project Settings.


#include "CharterChoice.h"

void UCharterChoice::NativeConstruct()
{
	back->OnClicked.AddDynamic(this, &UCharterChoice::Backclick);
	Character1->OnClicked.AddDynamic(this, &UCharterChoice::Character1Click);
	Character2->OnClicked.AddDynamic(this, &UCharterChoice::Character2Click);
	Character3->OnClicked.AddDynamic(this, &UCharterChoice::Character3Click);
	FText text = FText::FromString(TEXT("Auora"));
}



void UCharterChoice::Character1Click()
{
	FText text = FText::FromString(TEXT("Auora"));
	CharacterTitle->SetText(text);
	CharacterButtonChoice(CharacterChoice::Warrior);
}

void UCharterChoice::Character2Click()
{
	FText text = FText::FromString(TEXT("Gudion"));
	CharacterTitle->SetText(text);
	CharacterButtonChoice(CharacterChoice::Guiden);
}

void UCharterChoice::Character3Click()
{
	FText text = FText::FromString(TEXT("DarkMagion"));
	CharacterTitle->SetText(text);
	CharacterButtonChoice(CharacterChoice::DarkMagion);
}

void UCharterChoice::CharacterButtonChoice(CharacterChoice ch)
{
	AMainPlayerController* controller = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	if (ch == CharacterChoice::DarkMagion)
	{
		skill1_MA->SetVisibility(ESlateVisibility::Visible);
		skill2_MA->SetVisibility(ESlateVisibility::Visible);
		skill3_MA->SetVisibility(ESlateVisibility::Visible);
		skill4_MA->SetVisibility(ESlateVisibility::Visible);
		skill1->SetVisibility(ESlateVisibility::Collapsed);
		skill2->SetVisibility(ESlateVisibility::Collapsed);
		skill3->SetVisibility(ESlateVisibility::Collapsed);
		skill4->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		skill1_MA->SetVisibility(ESlateVisibility::Collapsed);
		skill2_MA->SetVisibility(ESlateVisibility::Collapsed);
		skill3_MA->SetVisibility(ESlateVisibility::Collapsed);
		skill4_MA->SetVisibility(ESlateVisibility::Collapsed);
		skill1->SetVisibility(ESlateVisibility::Visible);
		skill2->SetVisibility(ESlateVisibility::Visible);
		skill3->SetVisibility(ESlateVisibility::Visible);
		skill4->SetVisibility(ESlateVisibility::Visible);
	}
	if (controller)
	{
		AIntroSceneObject* levelob = Cast<AIntroSceneObject>(controller->GetLevelSceneObjectActor());
		if (levelob)
			levelob->CalltheSelectCharacter(ch);
	}
}

void UCharterChoice::Backclick()
{
	UIntroMainUI* ui = Cast<UIntroMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget());
	FText text = FText::FromString(TEXT("Auora"));
	CharacterTitle->SetText(text);
	if (ui)
	{
		ui->SetSwitcherIndex(0);
	
	}
}
