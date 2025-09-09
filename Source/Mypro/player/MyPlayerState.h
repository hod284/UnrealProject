// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "InventoryComponent.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)  const override;
	AMyPlayerState();
public:
	UPROPERTY(Replicated)
	TSubclassOf<APawn> SelectCharacter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	TObjectPtr<UInventoryComponent> Inventoryco;
	UPROPERTY(Replicated)
	Characters MyCharacter;
};
