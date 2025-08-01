// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../singleton/UImanager.h"
#include "Blueprint/UserWidget.h"
#include "CharterChoice.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UCharterChoice : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> back;
	virtual void NativeConstruct() override;
	UFUNCTION()
	void Backclick();
	
};
