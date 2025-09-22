// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPortalClass.h"

// Sets default values
ASpawnPortalClass::ASpawnPortalClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnPortalClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnPortalClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

