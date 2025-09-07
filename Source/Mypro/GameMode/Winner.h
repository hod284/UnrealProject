// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include  "../player/MainPlayerController.h"
#include  "../player/MyPlayerState.h"
#include  "../singleton/GameManager.h"
#include "GameFramework/GameModeBase.h"
#include "Winner.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API AWinner : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	AWinner();
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
