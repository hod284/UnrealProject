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
	UPROPERTY()
	TObjectPtr<UProgressBar> NormalAtk;
	UPROPERTY()
	TObjectPtr<UProgressBar> skill1Atk;
	UPROPERTY()
	TObjectPtr<UProgressBar> skill2Atk;
	UPROPERTY()
	TObjectPtr<UProgressBar> skill3Atk;
	UPROPERTY()
	TObjectPtr<UProgressBar> skill4Atk;
	void SetDataValue(Characters ch);
	UPROPERTY()
	TObjectPtr<UDataTable> chda;
	// findrow�� �޾ƿ� ��� �޾ƿö� const�� �޾ƿ��� ������ �޾ƿ��� �ν��Ͻ� ������ �����Ҷ��� const�� �ٿ����Ѵ�
	const FCharacterInfo* daInfo;
	virtual void NativeConstruct() override;
public:
	void SetData(Characters ch);
};
