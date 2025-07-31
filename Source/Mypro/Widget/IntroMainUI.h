// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "Blueprint/UserWidget.h"
#include "IntroMainUI.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UIntroMainUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void SetSwitcherIndex(int32 Index);

protected:
	UPROPERTY( meta = (BindWidget))	
	TObjectPtr<UWidgetSwitcher> Switcher;



	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};
