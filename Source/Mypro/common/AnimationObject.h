// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "UObject/NoExportTypes.h"
#include "AnimationObject.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UAnimationObject : public UObject
{
	GENERATED_BODY()
protected:
	// �÷��̾� �ִϸ��̼� ���� ������ 
	const FPlayerAnimInfo* DataAnimainfo_D;
	// �÷��̾� �ִϸ��̼� ���� ���е糲��
	const FPlayerAnimInfo* DataAnimainfo_G;
	// �÷��̾� �ִϸ��̼� ���� ������
	const FPlayerAnimInfo* DataAnimainfo_W;
	// �÷��̾� �ִϸ��̼� ���� ����
	const FMonsterAnimInfo* DataAnimainfo_Monster;
public:
	const FPlayerAnimInfo* GetAnimaDatainfo_W() const
	{
		return DataAnimainfo_W;
	}
	const FPlayerAnimInfo* GetAnimaDatainfo_G() const
	{
		return DataAnimainfo_G;
	}
	const FPlayerAnimInfo* GetAnimaDatainfo_D() const
	{
		return DataAnimainfo_D;
	}
	const  FMonsterAnimInfo* GetDataAnimainfo_Monster() const
	{
		return DataAnimainfo_Monster;
	}

	UAnimationObject();
};
