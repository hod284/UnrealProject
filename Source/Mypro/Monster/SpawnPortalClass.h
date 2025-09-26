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
	// Ãæµ¹
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);
	// ¿À¹ö·¦
	UFUNCTION()
	void OnCapsuleBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	// ¿À¹ö·¦ ³¡
	UFUNCTION()
	void OnCapsuleEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Spawn();

};
