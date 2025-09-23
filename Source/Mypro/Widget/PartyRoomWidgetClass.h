// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "SkillStatus.h"
#include "Blueprint/UserWidget.h"
#include "PartyRoomWidgetClass.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UPartyRoomWidgetClass : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USkillStatus> Skill1;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USkillStatus> Skill2;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USkillStatus> Skill3;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USkillStatus> Skill4;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UProgressBar> PlayerHp;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UProgressBar> PlayerMp;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UProgressBar> PlayerHp_other;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UProgressBar> PlayerMp_other;
	float Percent1 = 1.0f;

	float Percent2 = 1.0f;

	float Percent3 = 1.0f;

	float Percent4 = 1.0f;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	void SetSkill1Inite(FString Path);
	void SetSkill2Inite(FString Path);
	void SetSkill3Inite(FString Path);
	void SetSkill4Inite(FString Path);
	void SetPlayerImage(FString Path);
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
};
