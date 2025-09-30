// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../singleton/GameManager.h"
#include "../player/InventoryComponent.h"
#include "../common/MySingleton.h"
#include "InventorySlot.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

/**
 * 
 */

UCLASS()
class MYPRO_API UInventory : public UUserWidget
{
	GENERATED_BODY()
protected:

	TMap<FString, int32> ItemArray;
	TArray<TObjectPtr<UInventorySlot>> SlotArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UButton> Closebu;
	UInventoryComponent* InventoryComponent = nullptr;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	UFUNCTION()
	void Close();
	void AddInventory(FString name);
	void MinusInventory(FString name);
	TMap<FName, TObjectPtr<UTexture2D>>	textureMap;
	TMap<FName, TObjectPtr<UStaticMesh>> MeshMap;
public:
	void SetItemInventory(UInventoryComponent *compnent);
	UInventoryComponent* GetItemInventory() const
	{
		return 	InventoryComponent;
	}
};
