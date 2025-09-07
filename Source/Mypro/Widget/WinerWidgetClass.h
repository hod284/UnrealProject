// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "Blueprint/UserWidget.h"
#include "WinerWidgetClass.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UWinerWidgetClass : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TObjectPtr<UButton> GotoIntro;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UButton> Gameexit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UTextBlock> Winner;
	int32 TimeCount;
	FTimerHandle Timer;
	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;
	void Typing();
	UFUNCTION()
	void Gotointromethod();
	UFUNCTION()
	void GotoExit();
};
