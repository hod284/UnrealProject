// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "Blueprint/UserWidget.h"
#include "Slot.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API USlot : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized()override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct()override ;
    UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TObjectPtr<UImage> Image;
public:	
	void Inite(UTexture2D *im);
};
