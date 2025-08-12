// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataManager.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UDataManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
protected:

		virtual void Initialize(FSubsystemCollectionBase& Collection) override;
		// findrow로 받아올 경우 받아올때 const로 받아오기 때문에 받아오는 인스턴스 변수를 지정할때도 const로 붙여야한다
		// 여전사 정보
		const FCharacterInfo* Datainfo_W;
		// 방패든 남자 정보
		const FCharacterInfo* Datainfo_G;
		// 메지션 정보
		const FCharacterInfo* Datainfo_D;
		// 몬스터 정보
		const FCMonsterInfo* Datainfo_Monster;
		// 플레이어 애니메이션 정보 메지션 
		const FPlayerAnimInfo* DataAnimainfo_D;
		// 플레이어 애니메이션 정보 방패든남자
		const FPlayerAnimInfo* DataAnimainfo_G;
		// 플레이어 애니메이션 정보 여전사
		const FPlayerAnimInfo* DataAnimainfo_W;
		// 플레이어 애니메이션 정보 몬스터
		const FMonsterAnimInfo* DataAnimainfo_Monster;
public:
	const FCharacterInfo* GetDatainfo_W() const
	{
		return Datainfo_W;
	}
	const FCharacterInfo* GetDatainfo_G() const
	{
		return Datainfo_G;
	}
	const FCharacterInfo* GetDatainfo_D() const
	{
		return Datainfo_D;
	}
	const FCMonsterInfo* GetDatainfo_Monster() const
	{
		return Datainfo_Monster;
	}
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
};
