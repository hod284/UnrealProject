// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../common/MySingleton.h"
#include "../singleton/GameManager.h"
#include "../player/MyPlayerState.h"
#include "../player/MainPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "RoomWidgetClass.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API URoomWidgetClass : public UUserWidget
{
	GENERATED_BODY()
protected:
	AMainPlayerController* PC;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton> Start;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton> Ready;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton> Character1; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	Character2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	Character3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	Muteb;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeOnInitialized() override;
	UFUNCTION()
	void Character1Click(); 
	UFUNCTION()
	void Character2Click(); 
	UFUNCTION()
	void Character3Click(); 
	UFUNCTION()
	void ReadyButton();
	UFUNCTION()
	void GoTravel();
	UFUNCTION()
	void AudioMutemethod();
	UAudioComponent* SoundComp;
public:	
	void SetMeDiasound(UAudioComponent* Comp)
	{
		SoundComp = Comp;
	}
};
