// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterChoice.h"

void UCharacterChoice::NativeConstruct()
{
	back->OnClicked.AddDynamic(this, &UCharacterChoice::Backclick);
	Character1->OnClicked.AddDynamic(this, &UCharacterChoice::Character1Click);
	Character2->OnClicked.AddDynamic(this, &UCharacterChoice::Character2Click);
	Character3->OnClicked.AddDynamic(this, &UCharacterChoice::Character3Click);
	Start->OnClicked.AddDynamic(this, &UCharacterChoice::StartButtonClick);
}



void UCharacterChoice::Character1Click()
{
	FText text = FText::FromString(TEXT("Auora"));
	CharacterTitle->SetText(text);
	GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->SetTemp(Characters::Warrior);
	CharacterButtonChoice(Characters::Warrior);
}

void UCharacterChoice::Character2Click()
{
	FText text = FText::FromString(TEXT("Gudion"));
	CharacterTitle->SetText(text);
	GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->SetTemp(Characters::Guiden);
	CharacterButtonChoice(Characters::Guiden);
}

void UCharacterChoice::Character3Click()
{
	FText text = FText::FromString(TEXT("DarkMagion"));
	CharacterTitle->SetText(text);
	GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->SetTemp(Characters::DarkMagion);
	CharacterButtonChoice(Characters::DarkMagion);
}

void UCharacterChoice::StartButtonClick()
{
    GameStart(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->Gettemp());
}

void UCharacterChoice::CharacterButtonChoice(Characters ch)
{
	AMainPlayerController* controller = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	if (ch == Characters::DarkMagion)
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

void UCharacterChoice::GameStart(Characters ch)
{
	AMainPlayerController* controller = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetSelectCharacter(ch);
	if (controller)
	{
		AIntroSceneObject* levelob = Cast<AIntroSceneObject>(controller->GetLevelSceneObjectActor());
		if (levelob)
			levelob->CallthePlayCharacter(ch);
	}
}

void UCharacterChoice::Backclick()
{
	UIntroMainUI* ui = Cast<UIntroMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget());
	FText text = FText::FromString(TEXT("Auora"));
	CharacterTitle->SetText(text);
	if (ui)
	{
		ui->SetSwitcherIndex(0);
	
	}
}
