// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../singleton/UImanager.h"
#include "../player/MyCharacter.h"
#include "../Monster/SpawnPortalClass.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal")
	TObjectPtr<ASpawnPortalClass> Portal;
	FTimerHandle Timer;
	int32 AddMaxium = 0;
	int32 Maxium = 4;
	bool CanMaxium = false;
	bool ClientPawnSpawn=false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void MinusMaxium()
	{
		AddMaxium -= 1;
	}
};
