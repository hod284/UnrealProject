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
  인트로 씬에서 멀티인지 싱글인지 선택하는 위젯 
 */
UCLASS()
class MYPRO_API UFirstSelectMode : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SingleButton; // 싱글 플레이 버튼
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> MultiButton; // 멀티 플레이 버튼
	UPROPERTY(Transient,BlueprintReadOnly,  meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> single; // 싱글 플레이 버튼 호버 애니메이션
	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> multi; //  멀티 플레이 버튼 호버 애니메이션
	UFUNCTION()
	void HoverSingleButton(); // 싱글 플레이 버튼 호버 이벤트
	UFUNCTION()
	void UnHoverSingleButton(); // 싱글 플레이 버튼 언호버 이벤트
	UFUNCTION()
	void HoverMultiButton(); // 멀티 플레이 버튼 호버 이벤트
	UFUNCTION()
	void UnHoverMultiButton(); // 싱글 플레이 버튼 언호버 이벤트
	UFUNCTION()
	void ClickSingleButton(); // 싱글 플레이 버튼 클릭 이벤트
	UFUNCTION()
	void ClickMultiButton(); // 멀티 플레이 버튼 클릭 이벤트
	// Called when the game starts
	virtual void NativeConstruct() override;
	void FirstSelectCharacter(); // 버튼을 누르고 난뒤 처음 캐릭터 선택
};
