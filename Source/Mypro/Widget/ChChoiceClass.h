// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../player/MainPlayerController.h"
#include "../singleton/GameManager.h"
#include "../singleton/UImanager.h"
#include "../common/IntroSceneObject.h"
#include "PlayerStatePannel.h"
#include "Blueprint/UserWidget.h"
#include "ChChoiceClass.generated.h"

/**
  ĳ���� ����ȭ�� ���� Ŭ����
 */
UCLASS()
class MYPRO_API UChChoiceClass : public UUserWidget
{

	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton> back;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton> Character1; //  �˵�� �ִ� ����ĳ���� ���� ��ư
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	Character2;// ���п� ���� ��� �ִ� ���� ĳ���� ���� ��ư
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	Character3;// �ƹ��͵� �ȵ�� �ִ� ���� ĳ���� ���� ��ư
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton> skill1; //  skill1 ���� ��ư
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	skill2;// skill2 ���� ��ư
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	skill3;// skill3 ���� ��ư
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	skill4;// skill4 ���� ��ư
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton> skill1_MA; //  skill1 ������ ���� ��ư
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	skill2_MA;// skill2 ������ ���� ��ư
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	skill3_MA;// skill3 ������ ���� ��ư
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	skill4_MA;// skill4 ������ ���� ��ư
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTextBlock> Titletext; // ĳ���� Ÿ��Ʋ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton> Start; // ���� ��ŸƮ
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
	UFUNCTION()
	void StartButtonClick();

	void CharacterButtonChoice(Characters ch); // ĳ���� ���� �Լ�
	void GameStart(Characters ch); // ĳ���� ���� �Լ�

};
