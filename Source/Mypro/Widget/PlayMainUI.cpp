// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayMainUI.h"

void UPlayMainUI::NativeConstruct()
{
	Super::NativeConstruct();
	Skill1 = Cast<USkillStatus>(GetWidgetFromName("SkillUI1"));
	Skill2 = Cast<USkillStatus>(GetWidgetFromName("SkillUI2"));
	Skill3 = Cast<USkillStatus>(GetWidgetFromName("SkillUI3"));
	Skill4 = Cast<USkillStatus>(GetWidgetFromName("SkillUI4"));
	PlayerImage = Cast<UImage>(GetWidgetFromName("Playerimg"));
	PlayerHp =Cast<UProgressBar>(GetWidgetFromName("PlayerHP"));
	PlayerMp = Cast<UProgressBar>(GetWidgetFromName("PlayerMP"));
	MonsterHp = Cast<UProgressBar>(GetWidgetFromName("MHP"));
	MonsterStun = Cast<UProgressBar>(GetWidgetFromName("MST"));
}

UPlayMainUI::UPlayMainUI(const FObjectInitializer& ObjectInitializer):
UUserWidget(ObjectInitializer)
{
}
void UPlayMainUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) 
{
	Super::NativeTick( MyGeometry, InDeltaTime);
	Skill1->SetTIme(Percent1);
	Skill2-> SetTIme(Percent2);
	Skill3->SetTIme(Percent3); 
	Skill4 -> SetTIme(Percent4);
	if (Percent1 < 0.0)
		Percent1 = 1.0f;
	if (Percent2 < 0.0)
		Percent2 = 1.0f;
	if (Percent3 < 0.0)
		Percent3 = 1.0f;
	if (Percent4 < 0.0)
		Percent4 = 1.0f;
}
void UPlayMainUI::SetSkill1Inite(FString Path)
{
	Skill1 -> Setinit(Path, 1);
}
void UPlayMainUI::SetSkill2Inite(FString Path)
{
	Skill2->Setinit(Path, 1);
}
void UPlayMainUI::SetSkill3Inite(FString Path)
{
	Skill3->Setinit(Path, 1);
}
void UPlayMainUI::SetSkill4Inite(FString Path)
{
	Skill4->Setinit(Path, 1);
}
void UPlayMainUI::SetPlayerImage(FString Path)
{
	TSoftObjectPtr<UTexture2D> SoftTexture = TSoftObjectPtr<UTexture2D>(Path);
	PlayerImage->SetBrushFromSoftTexture(SoftTexture);
}