// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatePannel.h"

void UPlayerStatePannel::NativeConstruct()
{
	
}

void UPlayerStatePannel::SetData(Characters ch)
{
	UDataTable* chda = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/Character.Character"));
	switch (ch)
	{
	case Characters::Guiden:
		SetDataValue(ch, chda->FindRow<FCharacterInfo>("G", TEXT("")));
		break;

	}
}
void UPlayerStatePannel::SetDataValue(Characters ch, const FCharacterInfo* daInfo)
{
	float value = 100;
	float atk = static_cast<float>(daInfo->ATK);
	float skill1 = static_cast<float>(daInfo->Skill1_ATK);
	float skill2 = static_cast<float>(daInfo->Skill2_ATK);
	float skill3 = static_cast<float>(daInfo->Skill3_ATK);
	float skill4 = static_cast<float>(daInfo->Skill4_ATK);
	NormalAttack->SetPercent(atk/value);
	sk1->SetPercent(skill1/value);
	sk2->SetPercent(skill2/value);
	sk3->SetPercent(skill3/value);
	sk4->SetPercent(skill4/value);
}