// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../singleton/GameManager.h"
#include "../singleton/UImanager.h"
#include "GameFramework/Actor.h"
#include "RoomSceenController.generated.h"

UCLASS()
class MYPRO_API ARoomSceenController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomSceenController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float Pitch;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TObjectPtr<AStaticMeshActor>  SP1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<AStaticMeshActor>  SP2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<ACameraActor>  Camera;
	float Pitch_h;
	float Pitch_c;
	void GettheValue();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
