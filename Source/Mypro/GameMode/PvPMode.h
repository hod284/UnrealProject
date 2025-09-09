// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include  "../player/MainPlayerController.h"
#include "../player/MyCharacter.h"
#include  "../singleton/GameManager.h"
#include  "../player/MyPlayerState.h"
#include "GameFramework/GameModeBase.h"
#include "PvPMode.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API APvPMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	APvPMode();
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void RestartPlayer(AController* NewPlayer)override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
};
