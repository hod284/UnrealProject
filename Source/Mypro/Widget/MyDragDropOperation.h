// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "Blueprint/DragDropOperation.h"
#include "MyDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UMyDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:
	FString Itemname;
	FString  Count;
	UTexture2D* Texture;
	TWeakObjectPtr<class UInventorySlot> SourceSlot;
};
