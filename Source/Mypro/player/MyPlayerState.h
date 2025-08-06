// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	UFUNCTION(Server, Reliable)
	void SetMyCharacter(Characters character);


	UPROPERTY(Replicated)
	Characters MyCharacter;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)  const override;
};
