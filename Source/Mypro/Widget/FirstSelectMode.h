// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../singleton/UImanager.h"
#include "../player/MainPlayerController.h"
#include "../common/IntroSceneObject.h"
#include "IntroMainUI.h"
#include "Blueprint/UserWidget.h"
#include "FirstSelectMode.generated.h"

/**
  ��Ʈ�� ������ ��Ƽ���� �̱����� �����ϴ� ���� 
 */
UCLASS()
class MYPRO_API UFirstSelectMode : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SingleButton; // �̱� �÷��� ��ư
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> MultiButton; // ��Ƽ �÷��� ��ư
	UPROPERTY(Transient,BlueprintReadOnly,  meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> single; // �̱� �÷��� ��ư ȣ�� �ִϸ��̼�
	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> multi; //  ��Ƽ �÷��� ��ư ȣ�� �ִϸ��̼�
	UFUNCTION()
	void HoverSingleButton(); // �̱� �÷��� ��ư ȣ�� �̺�Ʈ
	UFUNCTION()
	void UnHoverSingleButton(); // �̱� �÷��� ��ư ��ȣ�� �̺�Ʈ
	UFUNCTION()
	void HoverMultiButton(); // ��Ƽ �÷��� ��ư ȣ�� �̺�Ʈ
	UFUNCTION()
	void UnHoverMultiButton(); // �̱� �÷��� ��ư ��ȣ�� �̺�Ʈ
	UFUNCTION()
	void ClickSingleButton(); // �̱� �÷��� ��ư Ŭ�� �̺�Ʈ
	UFUNCTION()
	void ClickMultiButton(); // ��Ƽ �÷��� ��ư Ŭ�� �̺�Ʈ
	// Called when the game starts
	virtual void NativeConstruct() override;
	void FirstSelectCharacter(); // ��ư�� ������ ���� ó�� ĳ���� ����
};
