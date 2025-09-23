// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterHPBar.h"

void UMonsterHPBar::NativeConstruct()
{
	MonsterHp = Cast<UProgressBar>(GetWidgetFromName("MHP"));
}

void UMonsterHPBar::SetHpBar(float Percent)
{
	MonsterHp->SetPercent(Percent);
}
