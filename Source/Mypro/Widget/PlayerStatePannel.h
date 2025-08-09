// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../singleton/DataManager.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatePannel.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UPlayerStatePannel : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> NormalAttack;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> sk1;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> sk2;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> sk3;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> sk4;
	void SetDataValue(Characters ch, const FCharacterInfo* daInfo);

	// findrow로 받아올 경우 받아올때 const로 받아오기 때문에 받아오는 인스턴스 변수를 지정할때도 const로 붙여야한다
	virtual void NativeConstruct() override;
public:
	void SetData(Characters ch);
};
