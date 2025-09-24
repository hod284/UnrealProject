// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../singleton/UImanager.h"
#include "../player/MyCharacter.h"
#include "GameFramework/Actor.h"
#include "PartyRoomController.generated.h"

UCLASS()
class MYPRO_API APartyRoomController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APartyRoomController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPartyRoomWidgetClass* ui;
	AMyCharacter* Mychar;
	AMyCharacter* HostPawn;
	AMyCharacter* ClientPawn;
	TArray<AActor*> Players;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
