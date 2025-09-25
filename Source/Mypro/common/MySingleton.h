// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "Engine/GameInstance.h"
#include "MySingleton.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UMySingleton : public UGameInstance
{
	GENERATED_BODY()
protected:
    UDataTable* datatable_C = nullptr;
    UDataTable* datatable_M = nullptr;
    UDataTable* datatable_Item = nullptr;
    UDataTable* datatable_Itemtexture = nullptr;
	TArray<FPrimaryAssetId> Assetids;
	UMySingleton();
	virtual void Init() override;

public:
	const FCharacterInfo* GetDatainfo_W()
	{
		for (auto& Assetid : Assetids)
		{
			FString name = Assetid.PrimaryAssetName.ToString();
			if (name == "Character")
			{
				UAssetManager& AssetManager = UAssetManager::Get();
				FAssetData data;
				AssetManager.GetPrimaryAssetData(Assetid, data);
				datatable_C = Cast<UDataTable>(data.GetAsset());
			}
		}
		return datatable_C->FindRow<FCharacterInfo>("W", TEXT(""));
	}
	const FCharacterInfo* GetDatainfo_G()
	{
		for (auto& Assetid : Assetids)
		{
			FString name = Assetid.PrimaryAssetName.ToString();
			if (name == "Character")
			{
				UAssetManager& AssetManager = UAssetManager::Get();
				FAssetData data;
				AssetManager.GetPrimaryAssetData(Assetid, data);
				datatable_C = Cast<UDataTable>(data.GetAsset());
			}
		}
		return datatable_C->FindRow<FCharacterInfo>("G", TEXT(""));
	}
	const FCharacterInfo* GetDatainfo_D()
	{
		for (auto& Assetid : Assetids)
		{
			FString name = Assetid.PrimaryAssetName.ToString();
			if (name == "Character")
			{
				UAssetManager& AssetManager = UAssetManager::Get();
				FAssetData data;
				AssetManager.GetPrimaryAssetData(Assetid, data);
				datatable_C = Cast<UDataTable>(data.GetAsset());
			}
		}
		return datatable_C->FindRow<FCharacterInfo>("D", TEXT(""));
	}
	const FCMonsterInfo* GetDatainfo_Monster() 
	{
		for (auto& Assetid : Assetids)
		{
			FString name = Assetid.PrimaryAssetName.ToString();
			if (name == "Monster")
			{
				UAssetManager& AssetManager = UAssetManager::Get();
				FAssetData data;
				AssetManager.GetPrimaryAssetData(Assetid, data);
				datatable_M = Cast<UDataTable>(data.GetAsset());
			}
		}
		return datatable_M->FindRow<FCMonsterInfo>("steel", TEXT(""));
	}
	const FCMonsterInfo* GetDatainfo_Minion()
	{
		for (auto& Assetid : Assetids)
		{
			FString name = Assetid.PrimaryAssetName.ToString();
			if (name == "Monster")
			{
				UAssetManager& AssetManager = UAssetManager::Get();
				FAssetData data;
				AssetManager.GetPrimaryAssetData(Assetid, data);
				datatable_M = Cast<UDataTable>(data.GetAsset());
			}
		}
		return datatable_M->FindRow<FCMonsterInfo>("minion", TEXT(""));
	}
	const FItemtableInfo* GetItemInfo() 
	{
		for (auto& Assetid : Assetids)
		{
			FString name = Assetid.PrimaryAssetName.ToString();
			if (name == "itemtable")
			{
				UAssetManager& AssetManager = UAssetManager::Get();
				FAssetData data;
				AssetManager.GetPrimaryAssetData(Assetid, data);
				datatable_Item = Cast<UDataTable>(data.GetAsset());
			}
		}
		return  datatable_Item->FindRow<FItemtableInfo>("common", TEXT(""));;
	}
	const FItmeTexturAndMeshInfo* GetTextureInfo()
	{
		for (auto& Assetid : Assetids)
		{
			FString name = Assetid.PrimaryAssetName.ToString();
			if (name == "ItemMeshandTexture")
			{
				UAssetManager& AssetManager = UAssetManager::Get();
				FAssetData data;
				AssetManager.GetPrimaryAssetData(Assetid, data);
				datatable_Itemtexture = Cast<UDataTable>(data.GetAsset());
			}
		}
		return datatable_Itemtexture->FindRow<FItmeTexturAndMeshInfo>("commont", TEXT(""));
	}
};
