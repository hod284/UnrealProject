// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "SkillStatus.h"
#include "Blueprint/UserWidget.h"
#include "PlayMainUI.generated.h"

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
	virtual void NativeConstruct() override;
public:

	UPlayMainUI(const FObjectInitializer& ObjectInitializer);
};
