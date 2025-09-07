// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../singleton/GameManager.h"
#include "../singleton/UImanager.h"
#include "../common/IntroSceneObject.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 gameinstance ->gamesubinstance ->levelload -> gamemode ->playercontroller ->charactercontroller
 */
UCLASS()
class MYPRO_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	TArray<AActor*>SceneActorList;
	AMainPlayerController();
	virtual void Tick(float DeltaTime) override;
public:

    AActor* GetLevelSceneObjectActor() const
    {
		
	   AActor* Choice  = nullptr;
	   for (AActor* Actor : SceneActorList)
	   {
	      	if (Actor->GetClass() == AIntroSceneObject :: StaticClass())
	      	{
	      		Choice = Actor;
				break;
			}
	   }
	   return Choice;
    }
	
	TSubclassOf<APawn> GetSelectCharactertClass();
	
};
