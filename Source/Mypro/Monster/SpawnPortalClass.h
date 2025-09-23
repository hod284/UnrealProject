// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "MinionMonster.h"
#include "GameFramework/Actor.h"
#include "SpawnPortalClass.generated.h"

UCLASS()
class MYPRO_API ASpawnPortalClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPortalClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UNiagaraComponent> Niagara1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UNiagaraComponent> Niagara2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UNiagaraComponent> Niagara3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UNiagaraComponent> Niagara4;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Monster")
	TSubclassOf<AMinionMonster> Minion;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Monster")
	TSubclassOf<AMinionMonster> Minion_gun;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
