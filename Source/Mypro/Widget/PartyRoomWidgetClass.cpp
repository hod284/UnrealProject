// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyRoomWidgetClass.h"
#include "../singleton/GameManager.h"
void UPartyRoomWidgetClass::NativeConstruct()
{
	Super::NativeConstruct();
	Skill1 = Cast<USkillStatus>(GetWidgetFromName("SkillUI1"));
	Skill2 = Cast<USkillStatus>(GetWidgetFromName("SkillUI2"));
	Skill3 = Cast<USkillStatus>(GetWidgetFromName("SkillUI3"));
	Skill4 = Cast<USkillStatus>(GetWidgetFromName("SkillUI4"));
	PlayerImage = Cast<UImage>(GetWidgetFromName("PImage"));
	PlayerHp = Cast<UProgressBar>(GetWidgetFromName("PHP"));
	PlayerMp = Cast<UProgressBar>(GetWidgetFromName("PMP"));
	Player_OtherImage = Cast<UImage>(GetWidgetFromName("OtherImage"));
	PlayerHp_other = Cast<UProgressBar>(GetWidgetFromName("OtherHP"));
	PlayerMp_other = Cast<UProgressBar>(GetWidgetFromName("OtherMP"));
}
void UPartyRoomWidgetClass::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	PC = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		if (PC->HasAuthority())
		{
			Skill1->SetTIme(Percent1);
			Skill2->SetTIme(Percent2);
			Skill3->SetTIme(Percent3);
			Skill4->SetTIme(Percent4);
		}
		else if (PC->IsLocalController())
		{
			Skill1->SetTIme(Percent1_c);
			Skill2->SetTIme(Percent2_c);
			Skill3->SetTIme(Percent3_c);
			Skill4->SetTIme(Percent4_c);
		}
	}
}
void UPartyRoomWidgetClass::SetSkill1Inite(FString Path)
{
	Skill1->Setinit(Path, 1);
}
void UPartyRoomWidgetClass::SetSkill2Inite(FString Path)
{
	Skill2->Setinit(Path, 1);
}
void UPartyRoomWidgetClass::SetSkill3Inite(FString Path)
{
	Skill3->Setinit(Path, 1);
}
void UPartyRoomWidgetClass::SetSkill4Inite(FString Path)
{
	Skill4->Setinit(Path, 1);
}
void UPartyRoomWidgetClass::SkillInite()
{
	switch (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSelectedcharacter())
	{
	case Characters::DarkMagion:
		SetSkill1Inite(TEXT("/Game/image/m1.m1"));
		SetSkill2Inite(TEXT("/Game/image/m2.m2"));
		SetSkill3Inite(TEXT("/Game/image/m3.m3"));
		SetSkill4Inite(TEXT("/Game/image/m4.m4"));
		SetPlayerImage(TEXT("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/giden.giden"));
		break;
	case Characters::Guiden:
		SetSkill1Inite(TEXT("/Game/image/1.1"));
		SetSkill2Inite(TEXT("/Game/image/2.2"));
		SetSkill3Inite(TEXT("/Game/image/3.3"));
		SetSkill4Inite(TEXT("/Game/image/4.4"));
		SetPlayerImage(TEXT("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/greyston.greyston"));
		break;
	case Characters::Warrior:
		SetSkill1Inite(TEXT("/Game/image/1.1"));
		SetSkill2Inite(TEXT("/Game/image/2.2"));
		SetSkill3Inite(TEXT("/Game/image/3.3"));
		SetSkill4Inite(TEXT("/Game/image/4.4"));
		SetPlayerImage(TEXT("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/Auraura.Auraura"));
		break;
	default:
		break;
	}
}
void UPartyRoomWidgetClass::SetPlayerImagebyCharacter(Characters ch)
{
	switch (ch)
	{
	case Characters::DarkMagion:
		SetPlayerImage("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/giden.giden");
		break;
	case Characters::Guiden:
		SetPlayerImage("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/greyston.greyston");
		break;
	case Characters::Warrior:
		SetPlayerImage("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/Auraura.Auraura");
		break;
	default:
		break;
	}
}
void UPartyRoomWidgetClass::SetPlayerOtherImagebyCharacter(Characters ch)
{
	switch (ch)
	{
	case Characters::DarkMagion:
		SetPlayOtherImage("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/giden.giden");
		break;
	case Characters::Guiden:
		SetPlayOtherImage("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/greyston.greyston");
		break;
	case Characters::Warrior:
		SetPlayOtherImage("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/Auraura.Auraura");
		break;
	default:
		break;
	}
}
void UPartyRoomWidgetClass::SetPlayOtherImage(FString Path)
{
	UTexture2D* SoftTexture = LoadObject<UTexture2D>(nullptr, *Path);
	Player_OtherImage ->SetBrushFromSoftTexture(SoftTexture);
}
void UPartyRoomWidgetClass::SetPlayerImage(FString Path)
{
	UTexture2D* SoftTexture = LoadObject<UTexture2D>(nullptr, *Path);
	PlayerImage->SetBrushFromSoftTexture(SoftTexture);
}
void UPartyRoomWidgetClass::SetPlayerHpBar(float da)
{
	PlayerHp->SetPercent(da);
}

void UPartyRoomWidgetClass::SetPlayerMpBar(float da)
{
	PlayerMp->SetPercent(da);
}

void UPartyRoomWidgetClass::SetotherHpBar(float da)
{
	PlayerHp_other->SetPercent(da);
}

void UPartyRoomWidgetClass::SetotherMpBar(float da)
{
	PlayerMp_other->SetPercent(da);
}
