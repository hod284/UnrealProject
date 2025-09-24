// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../Widget/PlayMainUI.h"
#include "../Widget/IntroMainUI.h"
#include "../Widget/RoomWidgetClass.h"
#include "../Widget//WinerWidgetClass.h"
#include "../Widget/PvPUIClass.h"
#include "../Widget/PartyRoomWidgetClass.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UImanager.generated.h"


UCLASS()
class MYPRO_API UUImanager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TSubclassOf<UPlayMainUI> PlayMainUI; 
	UPROPERTY()
	TSubclassOf<UIntroMainUI> IntroMainUI; 
	UPROPERTY()
	TSubclassOf<UWinerWidgetClass> WinerUI; 
	UPROPERTY()
	TSubclassOf<URoomWidgetClass> RoomUI; 
	UPROPERTY()
	TSubclassOf<UPvPUIClass> PvPUI; 
	UPROPERTY()
	TSubclassOf<UPartyRoomWidgetClass> PartyRoomUI; 
	UPROPERTY()
    TObjectPtr <UUserWidget> PlayMainUI_widget; 
	UPROPERTY()
	TObjectPtr<UUserWidget> IntroMainUI_widget; 
	UPROPERTY()
	TObjectPtr<UUserWidget> Winer_widget; 
	UPROPERTY()
	TObjectPtr<UUserWidget> Room_widget; 
	UPROPERTY()
	TObjectPtr<UUserWidget> PvP_widget; 
	UPROPERTY()
	TObjectPtr<UUserWidget> PartyRoom_widget; 

public:
	const TObjectPtr<UUserWidget> GetPlayMainUI_widget() const
	{
		
		return PlayMainUI_widget;
	}
	// �÷��̾����� ���� ���� ���� get
	const TObjectPtr<UUserWidget> GetIntroMainUI_widget() const
	{
		return IntroMainUI_widget;
	}
	const TObjectPtr<UUserWidget> GetWiner_widget() const
	{
		return Winer_widget;
	}
	const TObjectPtr<UUserWidget> GetRoom_widget() const
	{
		return Room_widget;
	}
	const TObjectPtr<UUserWidget> GetPvP_widget() const
	{
		return  PvP_widget;
	}
	const TObjectPtr<UUserWidget> GetPartyRoom_widget() const
	{
		return  PartyRoom_widget;
	}
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UUImanager();
};
