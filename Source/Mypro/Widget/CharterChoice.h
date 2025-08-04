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
	TObjectPtr<UButton> Character1; //  검들고 있는 여성캐릭터 선택 버튼
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>	Character2;// 방패와 검을 들고 있는 남성 캐릭터 선택 버튼
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>	Character3;// 아무것도 안들고 있는 남성 캐릭터 선택 버튼
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> skill1; //  skill1 선택 버튼
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>	skill2;// skill2 선택 버튼
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>	skill3;// skill3 선택 버튼
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>	skill4;// skill4 선택 버튼
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> skill1_MA; //  skill1 매지션 선택 버튼
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>	skill2_MA;// skill2 매지션 선택 버튼
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>	skill3_MA;// skill3 매지션 선택 버튼
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>	skill4_MA;// skill4 매지션 선택 버튼
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CharacterTitle; // 캐릭터 타이틀
	virtual void NativeConstruct() override;
public:
	UFUNCTION()
	void Backclick();
	UFUNCTION()
	void Character1Click(); // 검들고 있는 여성캐릭터 선택 버튼 클릭 이벤트
	UFUNCTION()
	void Character2Click(); // 방패와 검을 들고 있는 남성 캐릭터  선택 버튼 클릭 이벤트
	UFUNCTION()
	void Character3Click(); // 아무것도 안들고 있는 남성 캐릭터 선택 버튼 클릭 이벤트
	void CharacterButtonChoice(CharacterChoice ch); // 캐릭터 선택 함수
	

};
