// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayMainUI.h"

void UPlayMainUI::NativeConstruct()
{
	Skill1 = Cast<USkillStatus>(GetWidgetFromName("SkillUI1"));
	Skill2 = Cast<USkillStatus>(GetWidgetFromName("SkillUI2"));
	Skill3 = Cast<USkillStatus>(GetWidgetFromName("SkillUI3"));
	Skill4 = Cast<USkillStatus>(GetWidgetFromName("SkillUI4"));
}

UPlayMainUI::UPlayMainUI(const FObjectInitializer& ObjectInitializer):
UUserWidget(ObjectInitializer)
{
}
