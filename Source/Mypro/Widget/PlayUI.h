// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "SkillStatus.h"
#include "Blueprint/UserWidget.h"
#include "PlayUI.generated.h"
/**
 스킬및 플레이를 할때 이용할 UI 모아놓은 캔버스 위젯 클래스입니다.
 */
UCLASS()
class MYPRO_API UPlayUI : public UUserWidget
{
	GENERATED_BODY()
public:

	UPlayUI(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USkillStatus> Skill1;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USkillStatus> Skill2;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USkillStatus> Skill3;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USkillStatus> Skill4;
	virtual void NativeConstruct() override;
};
