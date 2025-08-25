// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill1_Actor.h"

// Sets default values
ASkill1_Actor::ASkill1_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkill1_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill1_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

