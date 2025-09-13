// Fill out your copyright notice in the Description page of Project Settings.


#include "PvPUIClass.h"
#include "../singleton/GameManager.h"
#include "../player/MyPlayerState.h"
void UPvPUIClass::NativeConstruct()
{
	Super::NativeConstruct();
	Skill1 = Cast<USkillStatus>(GetWidgetFromName("SkillUI1"));
	Skill2 = Cast<USkillStatus>(GetWidgetFromName("SkillUI2"));
	Skill3 = Cast<USkillStatus>(GetWidgetFromName("SkillUI3"));
	Skill4 = Cast<USkillStatus>(GetWidgetFromName("SkillUI4"));
	HostImage = Cast<UImage>(GetWidgetFromName("HostImage"));
	HostHp = Cast<UProgressBar>(GetWidgetFromName("HostMP"));
	HostMp = Cast<UProgressBar>(GetWidgetFromName("HostMP"));
	ClientImage = Cast<UImage>(GetWidgetFromName("ClientImage"));
	ClientHp = Cast<UProgressBar>(GetWidgetFromName("ClientHP"));
	ClientMp = Cast<UProgressBar>(GetWidgetFromName("ClientMP"));
}
void UPvPUIClass::SkillInite()
{
	switch (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSelectedcharacter())
	{
	case Characters::DarkMagion:
		SetSkill1Inite(TEXT("/Game/image/m1.m1"));
		SetSkill2Inite(TEXT("/Game/image/m2.m2"));
		SetSkill3Inite(TEXT("/Game/image/m3.m3"));
		SetSkill4Inite(TEXT("/Game/image/m4.m4"));
		break;
	case Characters::Guiden:
		SetSkill1Inite(TEXT("/Game/image/1.1"));
		SetSkill2Inite(TEXT("/Game/image/2.2"));
		SetSkill3Inite(TEXT("/Game/image/3.3"));
		SetSkill4Inite(TEXT("/Game/image/4.4"));
		break;
	case Characters::Warrior:
		SetSkill1Inite(TEXT("/Game/image/1.1"));
		SetSkill2Inite(TEXT("/Game/image/2.2"));
		SetSkill3Inite(TEXT("/Game/image/3.3"));
		SetSkill4Inite(TEXT("/Game/image/4.4"));
		break;
	default:
		break;
	}
}
void UPvPUIClass::SetHostImagebyCharacter(Characters ch)
{
	switch (ch)
	{
	case Characters::DarkMagion:
		SetHostImage("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/giden.giden");
		break;
	case Characters::Guiden:
		SetHostImage("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/greyston.greyston");
		break;
	case Characters::Warrior:
		SetHostImage("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/Auraura.Auraura");
		break;
	default:
		break;
	}
}
void UPvPUIClass::SetClientImagebyCharacter(Characters ch)
{
	switch (ch)
	{
	case Characters::DarkMagion:
		SetClientImage("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/giden.giden");
			break;
	case Characters::Guiden:
		SetClientImage("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/greyston.greyston");
			break;
	case Characters::Warrior:
		SetClientImage("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/Auraura.Auraura");
			break;
	default:
		break;
	}
}
void UPvPUIClass::SetHostImage(FString Path)
{
	UTexture2D* SoftTexture = LoadObject<UTexture2D>(nullptr, *Path);
	HostImage->SetBrushFromSoftTexture(SoftTexture);
}
void UPvPUIClass::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	PC = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		if (PC->HasAuthority())
		{
			AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
			PS->PlayerHP_H = HostHp->GetPercent();
			PS->PlayerMP_H = HostMp->GetPercent();
		}
		else
		{
			PC->Sever_SendtheClientHP(ClientHp->GetPercent());
			PC->Sever_SendtheClientMP(ClientMp->GetPercent());
		}
		Skill1->SetTIme(Percent1);
		Skill2->SetTIme(Percent2);
		Skill3->SetTIme(Percent3);
		Skill4->SetTIme(Percent4);
	}
}
void UPvPUIClass::SetClientImage(FString Path)
{
	UTexture2D* SoftTexture = LoadObject<UTexture2D>(nullptr, *Path);
	ClientImage->SetBrushFromSoftTexture(SoftTexture);
}
void UPvPUIClass::SetHostHpBar(float da)
{
	HostHp->SetPercent(da);
}
void UPvPUIClass::SetHostMpBar(float da)
{
	HostMp->SetPercent(da);
}
void UPvPUIClass::SetClientHpBar(float da)
{
	ClientHp->SetPercent(da);
}
void UPvPUIClass::SetClientMpBar(float da)
{
	ClientMp->SetPercent(da);
}
void UPvPUIClass::SetSkill1Inite(FString Path)
{
	Skill1->Setinit(Path, 1);
}
void UPvPUIClass::SetSkill2Inite(FString Path)
{
	Skill2->Setinit(Path, 1);
}
void UPvPUIClass::SetSkill3Inite(FString Path)
{
	Skill3->Setinit(Path, 1);
}
void UPvPUIClass::SetSkill4Inite(FString Path)
{
	Skill4->Setinit(Path, 1);
}