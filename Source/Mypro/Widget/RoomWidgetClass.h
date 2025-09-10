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
	TObjectPtr<UButton> skill1; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	skill2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	skill3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	skill4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton> skill1_MA; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	skill2_MA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	skill3_MA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UButton>	skill4_MA;
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	UFUNCTION()
	void Character1Click(); 
	UFUNCTION()
	void Character2Click(); 
	UFUNCTION()
	void Character3Click(); 
	void CharacterButtonChoice(Characters ch);
};
