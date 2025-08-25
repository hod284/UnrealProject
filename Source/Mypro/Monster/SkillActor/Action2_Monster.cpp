// Fill out your copyright notice in the Description page of Project Settings.


#include "Action2_Monster.h"

// Sets default values
AAction2_Monster::AAction2_Monster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAction2_Monster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAction2_Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

