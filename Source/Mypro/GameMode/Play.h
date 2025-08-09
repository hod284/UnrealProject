// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include  "../player/MainPlayerController.h"
#include  "../singleton/GameManager.h"
#include  "../player/MyPlayerState.h"
#include "GameFramework/GameModeBase.h"
#include "Play.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API APlay : public AGameModeBase
{
	GENERATED_BODY()
protected:
	APlay();
	virtual void BeginPlay() override;
};
