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
  캐릭터 선택화면 위젯 클래스
 */
UCLASS()
class MYPRO_API UChChoiceClass : public UUserWidget
{

	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton> back;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton> Character1; //  검들고 있는 여성캐릭터 선택 버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	Character2;// 방패와 검을 들고 있는 남성 캐릭터 선택 버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	Character3;// 아무것도 안들고 있는 남성 캐릭터 선택 버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton> skill1; //  skill1 선택 버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	skill2;// skill2 선택 버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	skill3;// skill3 선택 버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	skill4;// skill4 선택 버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton> skill1_MA; //  skill1 매지션 선택 버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	skill2_MA;// skill2 매지션 선택 버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	skill3_MA;// skill3 매지션 선택 버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	skill4_MA;// skill4 매지션 선택 버튼
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTextBlock> Titletext; // 캐릭터 타이틀
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton> Start; // 게임 스타트
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
	UFUNCTION()
	void StartButtonClick();

	void CharacterButtonChoice(Characters ch); // 캐릭터 선택 함수
	void GameStart(Characters ch); // 캐릭터 선택 함수

};
