// Fill out your copyright notice in the Description page of Project Settings.


#include "IntroSceneObject.h"

// Sets default values
AIntroSceneObject::AIntroSceneObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIntroSceneObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIntroSceneObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIntroSceneObject::CalltheSelectCharacter(CharacterChoice choice)
{
	// 티멥에 있는 캐릭터 클래스를 for문을 통해 전부초기화
	for (const TPair<CharacterChoice, ASelectCharacter*>& pair : SelectCharacterList)
		pair.Value->Inite();
	auto character = SelectCharacterList[choice];
	character->Selected();
}

void AIntroSceneObject::CallthePlayCharacter(CharacterChoice choice)
{
	// 티멥에 있는 캐릭터 클래스를 for문을 통해 전부초기화
	for (const TPair<CharacterChoice, ASelectCharacter*>& pair : SelectCharacterList)
		pair.Value->Inite();
	auto character = SelectCharacterList[choice];
	character->StartGame();
}

