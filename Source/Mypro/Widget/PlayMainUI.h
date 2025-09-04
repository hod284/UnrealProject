// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "Inventory.h"
#include "SkillStatus.h"
#include "Blueprint/UserWidget.h"
#include "PlayMainUI.generated.h"
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDamage_M, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStun, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDamage_P, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMp_P, float);
/**
 * 
 */
UCLASS()
class MYPRO_API UPlayMainUI : public UUserWidget
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
	TObjectPtr<UProgressBar>  MonsterHp;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UProgressBar> MonsterStun;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UImage> PlayerImage;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UInventory> Inventory;

	float Percent1 = 1.0f;

	float Percent2 = 1.0f;

	float Percent3 = 1.0f;

	float Percent4 = 1.0f;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	UFUNCTION()
	void SetStunBar(float da);
	UFUNCTION()
	void SetMHpBar(float da);
	UFUNCTION()
	void SetPHpBar(float da);
	UFUNCTION()
	void SetPMpBar(float da);
public:
	FOnDamage_M OnDamage_M;
	FOnStun OnStunDamage;
	FOnDamage_P OnDamage_P;
	FOnMp_P OnSyncMp_P;
	UPlayMainUI(const FObjectInitializer& ObjectInitializer);
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
	TObjectPtr<UInventory> GetInventory()
	{
		return  Inventory;
	}
};
