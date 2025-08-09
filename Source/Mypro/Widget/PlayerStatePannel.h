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

	// findrow�� �޾ƿ� ��� �޾ƿö� const�� �޾ƿ��� ������ �޾ƿ��� �ν��Ͻ� ������ �����Ҷ��� const�� �ٿ����Ѵ�
	virtual void NativeConstruct() override;
public:
	void SetData(Characters ch);
};
