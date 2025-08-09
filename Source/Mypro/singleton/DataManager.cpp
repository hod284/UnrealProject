// Fill out your copyright notice in the Description page of Project Settings.


#include "DataManager.h"

void UDataManager::Initialize(FSubsystemCollectionBase& Collection)
{
	UAssetManager& AssetManager = UAssetManager::Get();
	FPrimaryAssetType AssetType = FPrimaryAssetType(TEXT("DataTable"));
	TArray<FPrimaryAssetId> Assetids;
	AssetManager.GetPrimaryAssetIdList(AssetType,Assetids);
	if (Assetids.Num() == 0)
	{
		UE_LOG(LogMypro, Warning, TEXT("NULL"));
		return;
	}
	for (auto& Assetid :Assetids )
	{
		FString name = Assetid.PrimaryAssetName.ToString();
		if (name == "Character")
		{
			FAssetData data;
			AssetManager.GetPrimaryAssetData(Assetid, data);
			UDataTable* datatable = Cast<UDataTable>(data.GetAsset());
			if (datatable)
			{
				Datainfo_W = datatable->FindRow<FCharacterInfo>("A", TEXT(""));
				Datainfo_G = datatable->FindRow<FCharacterInfo>("G", TEXT(""));
				Datainfo_D = datatable->FindRow<FCharacterInfo>("D", TEXT(""));
			}
		}
	}

}
