// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include  "../singleton/GameManager.h"
#include "Blueprint/UserWidget.h"
#include "IntroMainUI.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UIntroMainUI : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetSwitcherIndex(int32 Index);
	void SetPercenttext(float pe);
	void VisuallyStart(ESlateVisibility visible);
	void SetMeDiasound(TObjectPtr <UMediaSoundComponent>  Comp)
	{
		SoundComp = Comp;
	}
protected:
	float  vo = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton> Start; // 게임 스타트
	UPROPERTY( meta = (BindWidget))	
	TObjectPtr<UWidgetSwitcher> Switcher;
	UPROPERTY()
	TObjectPtr<UTextBlock> laodingtitle;
	UPROPERTY()
	TObjectPtr<UTextBlock> percenttext;
	UPROPERTY()
	TObjectPtr<UButton> EscBu;
	UPROPERTY()
	TObjectPtr<UButton> MuteBu;
	UFUNCTION()
	void StartButtonClick();
	UFUNCTION()
	void EscClick();
	UFUNCTION()
	void AudioMutemethod();
	void GameStart(Characters ch); // 캐릭터 선택 함수
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;
	TObjectPtr <UMediaSoundComponent> SoundComp;
};
