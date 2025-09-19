// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "Blueprint/UserWidget.h"
#include "DamageShowing.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UDamageShowing : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTextBlock> Damageshwoing;
	virtual void NativeConstruct() override;
public:
	void SetDamag(float da);
};
