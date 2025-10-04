// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "SkillStatus.h"
#include "../player/MainPlayerController.h"
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
	TObjectPtr<UTextBlock> LoseTyping;
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
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UImage> PlayerImage;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UImage> 	Player_OtherImage;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	int32 TimeCount;
	FTimerHandle Timer;
	bool Lose = false;
	bool MonsterStop = false;
public:
	void TypingStart();
	void Typing();
	void SetPlayerImagebyCharacter(Characters ch);
	void SetPlayerOtherImagebyCharacter(Characters ch);
	AMainPlayerController* PC;
	void SetPlayOtherImage(FString Path);
	void SetPlayerImage(FString Path);
	void SetSkill1Inite(FString Path);
	void SetSkill2Inite(FString Path);
	void SetSkill3Inite(FString Path);
	void SetSkill4Inite(FString Path);
	void SkillInite();
	void SetPlayerHpBar(float da);
	void SetPlayerMpBar(float da);
	void SetotherHpBar(float da);
	void SetotherMpBar(float da);
	void SetPercent1(float pe)
	{
		Percent1 = pe;
	}
	float GetPercent1()
	{
		return Percent1;
	}
	void SetPercent1_c(float pe)
	{
		Percent1_c = pe;
	}
	float GetPercent1_c()
	{
		return Percent1_c;
	}
	void SetPercent2(float pe)
	{
		Percent2 = pe;
	}
	float GetPercent2()
	{
		return Percent2;
	}
	void SetPercent2_c(float pe)
	{
		Percent2_c = pe;
	}
	float GetPercent2_c()
	{
		return Percent2_c;
	}
	void SetPercent3(float pe)
	{
		Percent3 = pe;
	}
	float GetPercent3()
	{
		return Percent3;
	}
	void SetPercent3_c(float pe)
	{
		Percent3_c = pe;
	}
	float GetPercent3_c()
	{
		return Percent3_c;
	}
	void SetPercent4(float pe)
	{
		Percent4 = pe;
	}
	float GetPercent4()
	{
		return Percent4;
	}
	void SetPercent4_c(float pe)
	{
		Percent4_c = pe;
	}
	float GetPercent4_c()
	{
		return Percent4_c;
	}
	bool GetLose()
	{
		return Lose;
	}
	bool GetMonsterStop()
	{
		return  MonsterStop;
	}
	float Percent1 = 1.0f;
	float Percent1_c = 1.0f;
	float Percent2 = 1.0f;
	float Percent2_c = 1.0f;
	float Percent3 = 1.0f;
	float Percent3_c = 1.0f;
	float Percent4 = 1.0f;
	float Percent4_c = 1.0f;
};
