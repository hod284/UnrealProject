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
	virtual void BeginPlay() override;
	virtual void CopyProperties(APlayerState* NewPlayerState) override;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	TObjectPtr<UInventoryComponent> Inventoryco;
	UPROPERTY(Replicated)
	Characters MyCharacter_C = Characters::None;
	UPROPERTY(Replicated)
	Characters MyCharacter_H = Characters::None;
	UPROPERTY(Replicated)
	bool Ready_H;
	UPROPERTY(Replicated)
	bool Ready_C;
	UPROPERTY(Replicated)
	float Pitch_H;
	UPROPERTY(Replicated)
	float Pitch_C;
};
