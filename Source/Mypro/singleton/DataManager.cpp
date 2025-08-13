// Fill out your copyright notice in the Description page of Project Settings.


#include "DataManager.h"

void UDataManager::Initialize(FSubsystemCollectionBase& Collection)
{
	//에셋메니져 받아오기
	UAssetManager& AssetManager = UAssetManager::Get();
	// 언리얼에 있는 에셋메니저에 프라이머 에셋 타입 이름 적기
	FPrimaryAssetType AssetType = FPrimaryAssetType(TEXT("DataTable"));
	TArray<FPrimaryAssetId> Assetids;
	// 에셋 메이니저에서 에셋메니저에 있는 디렉터리 가져오기
	AssetManager.GetPrimaryAssetIdList(AssetType,Assetids);
	if (Assetids.Num() == 0)
	{
		UE_LOG(LogMypro, Warning, TEXT("NULL"));
		return;
	}
	for (auto& Assetid :Assetids )
	{
		FString name = Assetid.PrimaryAssetName.ToString();
	    // 디렉터리안에 파일중 이름 같은거 찾기
		if (name == "Character")
		{
			FAssetData data;
			AssetManager.GetPrimaryAssetData(Assetid, data);
			// 내가 정해진 프라이머 에셋 타입을 가져와서 대입시키기
			UDataTable* datatable = Cast<UDataTable>(data.GetAsset());
			if (datatable)
			{
				Datainfo_W = datatable->FindRow<FCharacterInfo>("W", TEXT(""));
				Datainfo_G = datatable->FindRow<FCharacterInfo>("G", TEXT(""));
				Datainfo_D = datatable->FindRow<FCharacterInfo>("D", TEXT(""));
			}
		}
		if (name == "Monster")
		{
			FAssetData data;
			AssetManager.GetPrimaryAssetData(Assetid, data);
			// 내가 정해진 프라이머 에셋 타입을 가져와서 대입시키기
			UDataTable* datatable = Cast<UDataTable>(data.GetAsset());
			if (datatable)
			{
				Datainfo_Monster = datatable->FindRow<FCMonsterInfo>("steel", TEXT(""));
			}
		}
	}

}
