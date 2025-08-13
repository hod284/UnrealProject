// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationObject.h"

UAnimationObject::UAnimationObject()
{
	UDataTable* mPlayerAnimData = NULL;
	static ConstructorHelpers::FObjectFinder<UDataTable>
		PlayerAnimTable(TEXT("/Script/Engine.DataTable'/Game/Data/PlayerAnimation.PlayerAnimation'"));

	if (PlayerAnimTable.Succeeded())
		mPlayerAnimData = PlayerAnimTable.Object;
	if (mPlayerAnimData)
	{
		DataAnimainfo_W =  mPlayerAnimData->FindRow<FPlayerAnimInfo>("Warrior", TEXT(""));
		DataAnimainfo_G =  mPlayerAnimData->FindRow<FPlayerAnimInfo>("Guidion", TEXT(""));
		DataAnimainfo_D =  mPlayerAnimData->FindRow<FPlayerAnimInfo>("DarkMagition", TEXT(""));
	}
	static ConstructorHelpers::FObjectFinder<UDataTable>
		PlayerAnimTable_monster(TEXT("/Script/Engine.DataTable'/Game/Data/MonsterAnimation.MonsterAnimation'"));
	if (PlayerAnimTable_monster.Succeeded())
		mPlayerAnimData = PlayerAnimTable_monster.Object;
	if (mPlayerAnimData)
	DataAnimainfo_Monster = mPlayerAnimData->FindRow<FMonsterAnimInfo>("Steel", TEXT(""));
}
