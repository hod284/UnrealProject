// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../singleton/GameManager.h"
#include  "../player/MyPlayerState.h"
#include "../player/MainPlayerController.h"
#include "GameFramework/GameModeBase.h"
#include "Room.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API ARoom : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	ARoom();
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
