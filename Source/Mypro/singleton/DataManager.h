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
		// findrow�� �޾ƿ� ��� �޾ƿö� const�� �޾ƿ��� ������ �޾ƿ��� �ν��Ͻ� ������ �����Ҷ��� const�� �ٿ����Ѵ�
		// ������ ����
		const FCharacterInfo* Datainfo_W;
		// ���е� ���� ����
		const FCharacterInfo* Datainfo_G;
		// ������ ����
		const FCharacterInfo* Datainfo_D;
		// ���� ����
		const FCMonsterInfo* Datainfo_Monster;
		// �÷��̾� �ִϸ��̼� ���� ������ 
		const FPlayerAnimInfo* DataAnimainfo_D;
		// �÷��̾� �ִϸ��̼� ���� ���е糲��
		const FPlayerAnimInfo* DataAnimainfo_G;
		// �÷��̾� �ִϸ��̼� ���� ������
		const FPlayerAnimInfo* DataAnimainfo_W;
		// �÷��̾� �ִϸ��̼� ���� ����
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
