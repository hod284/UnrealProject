// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatePannel.h"

void UPlayerStatePannel::NativeConstruct()
{
	NormalAtk = Cast<UProgressBar>(GetWidgetFromName("NormalAttack"));
	skill1Atk = Cast<UProgressBar>(GetWidgetFromName("skill1"));
	skill2Atk = Cast<UProgressBar>(GetWidgetFromName("skill2"));
	skill3Atk = Cast<UProgressBar>(GetWidgetFromName("skill3"));
	skill4Atk = Cast<UProgressBar>(GetWidgetFromName("skill4"));
}

void UPlayerStatePannel::SetData(Characters ch)
{
	chda = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/Data/Character.Character'"));
	switch (ch)
	{
	case Characters::Guiden:
	    daInfo = chda->FindRow<FCharacterInfo>("A",TEXT(""));
		SetDataValue(ch);
		break;
	
	}
}
void UPlayerStatePannel::SetDataValue(Characters ch)
{
	float value = 100.0f;
		NormalAtk->SetPercent(daInfo->ATK / value);
		skill1Atk->SetPercent(daInfo->Skill1_ATK / value);;
		skill2Atk->SetPercent(daInfo->Skill2_ATK / value);;
		skill3Atk->SetPercent(daInfo->Skill3_ATK / value);;;
		skill4Atk->SetPercent(daInfo->Skill4_ATK / value);;;
		
}
