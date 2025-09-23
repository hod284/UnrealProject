// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "Blueprint/UserWidget.h"
#include "MonsterHPBar.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UMonsterHPBar : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UProgressBar> MonsterHp;
	virtual void NativeConstruct() override;
public:
	void SetHpBar(float Percent);
};
