// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../singleton/UImanager.h"
#include "../player/SelectCharacter.h"
#include "../singleton/GameManager.h"
#include "GameFramework/Actor.h"
#include "WinLevelController.generated.h"

UCLASS()
class MYPRO_API AWinLevelController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWinLevelController();

protected:
	// Called when the game starts or when spawned
	float cameratime=4.0;
	APlayerController* PlayerController;
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	TObjectPtr<APawn> Auroa;
	UPROPERTY(EditAnywhere)
	TObjectPtr<APawn> Giden;
	UPROPERTY(EditAnywhere)
	TObjectPtr<APawn> GraySton;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
