// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../player/MainPlayerController.h"
#include "../singleton/UImanager.h"
#include "../common/IntroSceneObject.h"
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
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Character1; //  �˵�� �ִ� ����ĳ���� ���� ��ư
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>	Character2;// ���п� ���� ��� �ִ� ���� ĳ���� ���� ��ư
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>	Character3;// �ƹ��͵� �ȵ�� �ִ� ���� ĳ���� ���� ��ư
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> skill1; //  skill1 ���� ��ư
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>	skill2;// skill2 ���� ��ư
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>	skill3;// skill3 ���� ��ư
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>	skill4;// skill4 ���� ��ư
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> skill1_MA; //  skill1 ������ ���� ��ư
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>	skill2_MA;// skill2 ������ ���� ��ư
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>	skill3_MA;// skill3 ������ ���� ��ư
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>	skill4_MA;// skill4 ������ ���� ��ư
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CharacterTitle; // ĳ���� Ÿ��Ʋ
	virtual void NativeConstruct() override;
public:
	UFUNCTION()
	void Backclick();
	UFUNCTION()
	void Character1Click(); // �˵�� �ִ� ����ĳ���� ���� ��ư Ŭ�� �̺�Ʈ
	UFUNCTION()
	void Character2Click(); // ���п� ���� ��� �ִ� ���� ĳ����  ���� ��ư Ŭ�� �̺�Ʈ
	UFUNCTION()
	void Character3Click(); // �ƹ��͵� �ȵ�� �ִ� ���� ĳ���� ���� ��ư Ŭ�� �̺�Ʈ
	void CharacterButtonChoice(CharacterChoice ch); // ĳ���� ���� �Լ�
	

};
