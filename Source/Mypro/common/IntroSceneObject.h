// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../player/SelectCharacter.h"
#include "GameFramework/Actor.h"
#include "IntroSceneObject.generated.h"

UCLASS()
class MYPRO_API AIntroSceneObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIntroSceneObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "listofSelctcharacter")
	TMap<Characters, ASelectCharacter*> SelectCharacterList; // 캐릭터 리스트

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void CalltheSelectCharacter(Characters choice); // 캐릭터 선택 함수
	void CallthePlayCharacter(Characters choice); // 본게임에 들어갈때 플레이 할 캐릭터 선택
};
