// Fill out your copyright notice in the Description page of Project Settings.


#include "MySingleton.h"

UMySingleton::UMySingleton()
{
}

void UMySingleton::Init()
{
	Super::Init();
	UAssetManager& AssetManager = UAssetManager::Get();
	FPrimaryAssetType AssetType = FPrimaryAssetType(TEXT("DataTable"));
	AssetManager.GetPrimaryAssetIdList(AssetType, Assetids);
	if (Assetids.Num() == 0)
	{
		UE_LOG(LogMypro, Warning, TEXT("NULL"));
		return;
	}
}
