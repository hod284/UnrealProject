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
	// 플레이어 애니메이션 정보 메지션 
	const FPlayerAnimInfo* DataAnimainfo_D;
	// 플레이어 애니메이션 정보 방패든남자
	const FPlayerAnimInfo* DataAnimainfo_G;
	// 플레이어 애니메이션 정보 여전사
	const FPlayerAnimInfo* DataAnimainfo_W;
	// 플레이어 애니메이션 정보 몬스터
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
