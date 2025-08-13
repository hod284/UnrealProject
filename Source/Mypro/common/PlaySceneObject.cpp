// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaySceneObject.h"

// Sets default values
APlaySceneObject::APlaySceneObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlaySceneObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlaySceneObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

