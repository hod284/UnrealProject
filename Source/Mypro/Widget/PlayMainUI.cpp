// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayMainUI.h"
#include "../common/PlaySceneObject.h"
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

	FDelegateHandle Handle1 =  OnDamage_M.AddUObject(this,&UPlayMainUI::SetMHpBar);
	FDelegateHandle Handle2  = OnStunDamage.AddUObject(this,&UPlayMainUI::SetStunBar);
	FDelegateHandle Handle3 =  OnDamage_P.AddUObject(this,&UPlayMainUI::SetPHpBar);
	FDelegateHandle Handle4 = OnSyncMp_P.AddUObject(this, &UPlayMainUI::SetPMpBar);
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
}
void UPlayMainUI::SetStunBar(float da)
{
	MonsterStun->SetPercent(da);
}
void UPlayMainUI::SetMHpBar(float da)
{
	MonsterHp->SetPercent(da);
}
void UPlayMainUI::SetPMpBar(float da)
{
	PlayerMp->SetPercent(da);
}
void UPlayMainUI::SetPHpBar(float da)
{
	PlayerHp->SetPercent(da);
}
void UPlayMainUI::SetSkill1Inite(FString Path)
{
	Skill1->Setinit(Path, 1);
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