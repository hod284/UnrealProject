// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

void UInventory::NativeConstruct()
{
	for (int32 i = 0; i < 4; ++i)
	{
		FString s = FString::FromInt(i);
		UInventorySlot* InventorySlot = Cast<UInventorySlot>(GetWidgetFromName(*s));
	    SlotArray.Add(InventorySlot);
	}
	Closebu = Cast<UButton>(GetWidgetFromName(TEXT("clo")));
	if(!Closebu->OnClicked.IsBound())
	Closebu->OnClicked.AddDynamic(this,&UInventory::Close);
	UMySingleton* GI = Cast<UMySingleton>(UGameplayStatics::GetGameInstance(GetWorld()));
	const FItmeTexturAndMeshInfo* Texture = GI->GetTextureInfo();
	textureMap = Texture->textureMap;
	MeshMap = Texture->MeshMap;
}

void UInventory::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	
}

void UInventory::AddInventory(FString name)
{
	if (textureMap.Contains(FName(*name)))
	{
		if (!ItemArray.Contains(name))
		{
			ItemArray.Add(name, 1);
			for (UInventorySlot* sl : SlotArray)
			{
				if (!sl->GetNotEmpty())
				{
					sl->SetTexture(textureMap[FName(*name)]);
					sl->Settext("1");
					sl->SetName(name);
					sl->SetNotEmpty(true);
					break;
				}
			}
		}
		else
		{
			ItemArray[name] += 1;
			for (UInventorySlot* sl : SlotArray)
			{
				if (sl->GetName() == name)
				{
					sl->Settext(FString::FromInt(ItemArray[name]));
				}
			}
		}
	}
}

void UInventory::MinusInventory(FString name)
{
	if (ItemArray.Contains(name) && !ItemArray.IsEmpty() && ItemArray[name] > 1)
	{
		ItemArray[name] -= 1;
		for (UInventorySlot* sl : SlotArray)
		{
			if (sl->GetName() == name)
			{
				sl->Settext(FString::FromInt(ItemArray[name]));
			}
		}
	}
	else if (ItemArray[name] == 1)
	{
		ItemArray.Remove(name);
		for (UInventorySlot* sl : SlotArray)
		{
			sl->SetTexture(NULL);
			sl->Settext("0");
			sl->SetName("");
			sl->SetNotEmpty(false);
			break;

		}
	}
}

void UInventory::SetItemInventory(UInventoryComponent* compnent)
{
	if (!IsValid(InventoryComponent))
	{
	    InventoryComponent = compnent;
		FDelegateHandle Handle1 = InventoryComponent->Itemadd.AddUObject(this, &UInventory::AddInventory);
		FDelegateHandle Handle2 = InventoryComponent->ItemMinus.AddUObject(this, &UInventory::MinusInventory);
	}
}
void UInventory::Close()
{
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetCusorVisual(UIORNOT::UINot);
	SetVisibility(ESlateVisibility::Collapsed);
}