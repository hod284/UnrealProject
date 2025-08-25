// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../Monster/Monster.h"
#include  "../player/MainPlayerController.h"
#include "GameFramework/Actor.h"
#include "PlaySceneObject.generated.h"


UCLASS()
class MYPRO_API APlaySceneObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaySceneObject();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cutscene")
	TObjectPtr<ULevelSequence> CutsceneSequence;
	TObjectPtr <ULevelSequencePlayer> SequencePlayer;
	ALevelSequenceActor* SequenceActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cutscene")
	TObjectPtr<ACameraActor> CineCamera;
	// 시퀀스 플레이
	void PlaySequence();
	UFUNCTION()
	void OnSequenceFinished();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TArray<AActor*> FoundActors_M;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	AActor* GetMonster(FString Name)
	{
		AActor* actor = nullptr;
		if (FoundActors_M.Num()>0)
		{
			for (auto ac: FoundActors_M)
			{
				if(ac->GetActorLabel() == Name)
				{
					actor = ac;
					break;
				}
			}
		}
		return actor;
	}

};
