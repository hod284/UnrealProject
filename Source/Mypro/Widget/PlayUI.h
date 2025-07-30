// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "SkillStatus.h"
#include "Blueprint/UserWidget.h"
#include "PlayUI.generated.h"
/**
 ��ų�� �÷��̸� �Ҷ� �̿��� UI ��Ƴ��� ĵ���� ���� Ŭ�����Դϴ�.
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
