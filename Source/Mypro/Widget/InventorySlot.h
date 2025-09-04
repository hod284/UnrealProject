// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "Slot.h"
#include "MyDragDropOperation.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UImage> Icon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UTextBlock> Countst;
	TSubclassOf<USlot>  SlotClass;
	FString Itemname;
	bool NotEmpty;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)override;
public:
	void Init(UTexture2D* im, int32 count, FString name);
	void SetTexture(UTexture2D* im);
	void Settext(FString Count);
	FString GetName()const
	{
		return  Itemname;
	}
	bool GetNotEmpty()const
	{
		return  NotEmpty;
	}
	void SetNotEmpty(bool bo)
	{
		 NotEmpty =bo;
	}
	void SetName(FString na)
	{
		Itemname =na;
	}

	UInventorySlot(const FObjectInitializer& ObjectInitializer);
};
