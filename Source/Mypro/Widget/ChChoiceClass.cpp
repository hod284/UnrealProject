// Fill out your copyright notice in the Description page of Project Settings.


#include "ChChoiceClass.h"

void UChChoiceClass::NativeConstruct()
{
	Titletext = Cast<UTextBlock>(GetWidgetFromName("Title"));
	Character1 = Cast<UButton>(GetWidgetFromName("ch1"));
	Character2 = Cast<UButton>(GetWidgetFromName("ch2"));
	Character3 = Cast<UButton>(GetWidgetFromName("ch3"));
	back = Cast<UButton>(GetWidgetFromName("backbutton"));
	Start = Cast<UButton>(GetWidgetFromName("Startbutton"));
	skill1 = Cast<UButton>(GetWidgetFromName("skill1b"));
	skill2 = Cast<UButton>(GetWidgetFromName("skill2b"));
	skill3 = Cast<UButton>(GetWidgetFromName("skill3b"));
	skill4 = Cast<UButton>(GetWidgetFromName("skill4b"));
	skill1_MA = Cast<UButton>(GetWidgetFromName("skill1b_ma"));
	skill2_MA = Cast<UButton>(GetWidgetFromName("skill2b_ma"));
	skill3_MA = Cast<UButton>(GetWidgetFromName("skill3b_ma"));
	skill4_MA = Cast<UButton>(GetWidgetFromName("skill4b_ma"));
	NormalAtk = Cast<UProgressBar>(GetWidgetFromName("NormalAttack"));
	skill1Atk = Cast<UProgressBar>(GetWidgetFromName("sk1"));
	skill2Atk = Cast<UProgressBar>(GetWidgetFromName("sk2"));
	skill3Atk = Cast<UProgressBar>(GetWidgetFromName("sk3"));
	skill4Atk = Cast<UProgressBar>(GetWidgetFromName("sk4"));
	back->OnClicked.AddDynamic(this, &UChChoiceClass::Backclick);
	Character1->OnClicked.AddDynamic(this, &UChChoiceClass::Character1Click);
	Character2->OnClicked.AddDynamic(this, &UChChoiceClass::Character2Click);
	Character3->OnClicked.AddDynamic(this, &UChChoiceClass::Character3Click);
	Start->OnClicked.AddDynamic(this, &UChChoiceClass::StartButtonClick);
	SetDataValue(Characters::Warrior, GetWorld()->GetGameInstance()->GetSubsystem<UDataManager>()->GetDatainfo_W());
}




void UChChoiceClass::Character1Click()
{
	FText text = FText::FromString(TEXT("Auora"));
	Titletext->SetText(text);
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetSelectCharacter(Characters::Warrior);
	CharacterButtonChoice(Characters::Warrior);
	SetDataValue(Characters::Warrior, GetWorld()->GetGameInstance()->GetSubsystem<UDataManager>()->GetDatainfo_W());
}

void UChChoiceClass::Character2Click()
{
	FText text = FText::FromString(TEXT("Gudion"));
	Titletext->SetText(text);
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetSelectCharacter(Characters::Guiden);
	CharacterButtonChoice(Characters::Guiden);
	SetDataValue(Characters::Guiden, GetWorld()->GetGameInstance()->GetSubsystem<UDataManager>()->GetDatainfo_G());
}

void UChChoiceClass::Character3Click()
{
	FText text = FText::FromString(TEXT("DarkMagion"));
	Titletext->SetText(text);
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetSelectCharacter(Characters::DarkMagion);
	CharacterButtonChoice(Characters::DarkMagion);
	UDataTable* MyTablechda = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/Character.Character"));
	SetDataValue(Characters::DarkMagion, GetWorld()->GetGameInstance()->GetSubsystem<UDataManager>()->GetDatainfo_D());
}

void UChChoiceClass::StartButtonClick()
{
	GameStart(GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSelectedcharacter());
}

void UChChoiceClass::CharacterButtonChoice(Characters ch)
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

void UChChoiceClass::GameStart(Characters ch)
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

void UChChoiceClass::Backclick()
{
	UIntroMainUI* ui = Cast<UIntroMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget());
	FText text = FText::FromString(TEXT("Auora"));
	SetDataValue(Characters::Warrior, GetWorld()->GetGameInstance()->GetSubsystem<UDataManager>()->GetDatainfo_W());
	Titletext->SetText(text);
	if (ui)
	{
		ui->SetSwitcherIndex(0);

	}
}
void UChChoiceClass::SetDataValue(Characters ch, const FCharacterInfo* daInfo)
{
	float value = 100;
	float atk = static_cast<float>(daInfo->ATK);
	float skill1_v = static_cast<float>(daInfo->Skill1_ATK);
	float skill2_v = static_cast<float>(daInfo->Skill2_ATK);
	float skill3_v = static_cast<float>(daInfo->Skill3_ATK);
	float skill4_v = static_cast<float>(daInfo->Skill4_ATK);
	NormalAtk->SetPercent(atk / value);
	skill1Atk->SetPercent(skill1_v / value);
	skill2Atk->SetPercent(skill2_v / value);
	skill3Atk->SetPercent(skill3_v / value);
	skill4Atk->SetPercent(skill4_v / value);
}