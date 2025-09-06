// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include  "../player/MyPlayerState.h"
#include  "../player/MainPlayerController.h"
#include  "../singleton/GameManager.h"
#include "GameFramework/GameModeBase.h"
#include "Intro.generated.h"


UCLASS()
class MYPRO_API AIntro : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	
	virtual void BeginPlay() override;
	AIntro();
};
