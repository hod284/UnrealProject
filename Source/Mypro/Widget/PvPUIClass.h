// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../player/MainPlayerController.h"
#include "SkillStatus.h"
#include "Blueprint/UserWidget.h"
#include "PvPUIClass.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UPvPUIClass : public UUserWidget
{
	GENERATED_BODY()
public:
	void SkillInite();
	void SetHostHpBar(float da);
	void SetHostMpBar(float da);
	void SetClientHpBar(float da);
	void SetClientMpBar(float da);
	void SetHostImagebyCharacter(Characters ch);
	void SetClientImagebyCharacter(Characters ch);
	void SetPercent1(float pe)
	{
		Percent1 = pe;
	}
	float GetPercent1()
	{
		return Percent1;
	}
	void SetPercent2(float pe)
	{
		Percent2 = pe;
	}
	float GetPercent2()
	{
		return Percent2;
	}
	void SetPercent3(float pe)
	{
		Percent3 = pe;
	}
	float GetPercent3()
	{
		return Percent3;
	}
	void SetPercent4(float pe)
	{
		Percent4 = pe;
	}
	float GetPercent4()
	{
		return Percent4;
	}
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	AMainPlayerController* PC;	
	void SetClientImage(FString Path);
	void SetHostImage(FString Path);
	virtual void NativeConstruct() override;
	void SetSkill1Inite(FString Path);
	void SetSkill2Inite(FString Path);
	void SetSkill3Inite(FString Path);
	void SetSkill4Inite(FString Path);
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USkillStatus> Skill1;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USkillStatus> Skill2;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USkillStatus> Skill3;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USkillStatus> Skill4;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UProgressBar>  HostHp;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UProgressBar> HostMp;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UProgressBar>  ClientHp;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UProgressBar> ClientMp;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UImage> ClientImage;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UImage> HostImage;
	float Percent1 = 1.0f;
	float Percent2 = 1.0f;
	float Percent3 = 1.0f;
	float Percent4 = 1.0f;

};
