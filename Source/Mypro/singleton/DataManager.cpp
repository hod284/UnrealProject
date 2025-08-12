// Fill out your copyright notice in the Description page of Project Settings.


#include "DataManager.h"

void UDataManager::Initialize(FSubsystemCollectionBase& Collection)
{
	//���¸޴��� �޾ƿ���
	UAssetManager& AssetManager = UAssetManager::Get();
	// �𸮾� �ִ� ���¸޴����� �����̸� ���� Ÿ�� �̸� ����
	FPrimaryAssetType AssetType = FPrimaryAssetType(TEXT("DataTable"));
	TArray<FPrimaryAssetId> Assetids;
	// ���� ���̴������� ���¸޴����� �ִ� ���͸� ��������
	AssetManager.GetPrimaryAssetIdList(AssetType,Assetids);
	if (Assetids.Num() == 0)
	{
		UE_LOG(LogMypro, Warning, TEXT("NULL"));
		return;
	}
	for (auto& Assetid :Assetids )
	{
		FString name = Assetid.PrimaryAssetName.ToString();
	    // ���͸��ȿ� ������ �̸� ������ ã��
		if (name == "Character")
		{
			FAssetData data;
			AssetManager.GetPrimaryAssetData(Assetid, data);
			// ���� ������ �����̸� ���� Ÿ���� �����ͼ� ���Խ�Ű��
			UDataTable* datatable = Cast<UDataTable>(data.GetAsset());
			if (datatable)
			{
				Datainfo_W = datatable->FindRow<FCharacterInfo>("A", TEXT(""));
				Datainfo_G = datatable->FindRow<FCharacterInfo>("G", TEXT(""));
				Datainfo_D = datatable->FindRow<FCharacterInfo>("D", TEXT(""));
			}
		}
		if (name == "PlayerAnimation")
		{
			FAssetData data;
			AssetManager.GetPrimaryAssetData(Assetid, data);
			// ���� ������ �����̸� ���� Ÿ���� �����ͼ� ���Խ�Ű��
			UDataTable* datatable = Cast<UDataTable>(data.GetAsset());
			if (datatable)
			{
				DataAnimainfo_W = datatable->FindRow<FPlayerAnimInfo>("Warrior", TEXT(""));
				DataAnimainfo_G = datatable->FindRow<FPlayerAnimInfo>("Guidion", TEXT(""));
				DataAnimainfo_D = datatable->FindRow<FPlayerAnimInfo>("DarkMagition", TEXT(""));
			}
		}
		if (name == "Monster")
		{
			FAssetData data;
			AssetManager.GetPrimaryAssetData(Assetid, data);
			// ���� ������ �����̸� ���� Ÿ���� �����ͼ� ���Խ�Ű��
			UDataTable* datatable = Cast<UDataTable>(data.GetAsset());
			if (datatable)
			{
				Datainfo_Monster = datatable->FindRow<FCMonsterInfo>("steel", TEXT(""));
			}
		}
		if (name == "MonsterAnimation")
		{
			FAssetData data;
			AssetManager.GetPrimaryAssetData(Assetid, data);
			// ���� ������ �����̸� ���� Ÿ���� �����ͼ� ���Խ�Ű��
			UDataTable* datatable = Cast<UDataTable>(data.GetAsset());
			if (datatable)
			{
				DataAnimainfo_Monster = datatable->FindRow<FMonsterAnimInfo>("Steel", TEXT(""));
			}
		}
	}

}
