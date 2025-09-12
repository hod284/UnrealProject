// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../singleton/UImanager.h"
#include "GameFramework/Actor.h"
#include "PVPController.generated.h"

UCLASS()
class MYPRO_API APVPController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APVPController();

protected:
	FTimerHandle Timer;
	UPvPUIClass* ui;
	TArray<AActor*> Players;
	ACharacter* HostPawn;
	ACharacter* ClientPawn;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
