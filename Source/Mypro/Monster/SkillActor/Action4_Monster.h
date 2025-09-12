// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Gameinfo.h"
#include "GameFramework/Actor.h"
#include "Action4_Monster.generated.h"

UCLASS()
class MYPRO_API AAction4_Monster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAction4_Monster();

protected:
	FTimerHandle Time_Colider;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UNiagaraComponent> NiagaraParticle1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UCapsuleComponent> BoxColider1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UNiagaraComponent> NiagaraParticle2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UCapsuleComponent> BoxColider2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UNiagaraComponent> NiagaraParticle3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UCapsuleComponent> BoxColider3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UNiagaraComponent> NiagaraParticle4;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UCapsuleComponent> BoxColider4;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 AttackDamage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<USceneComponent> Transform;
	// Ãæµ¹
	UFUNCTION()
	void OnHit_Action4_M(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);
	// ¿À¹ö·¦
	UFUNCTION()
	void OnCapsuleBeginOverlap_Action4_M(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	// ¿À¹ö·¦ ³¡
	UFUNCTION()
	void OnCapsuleEndOverlap_Action4_M(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	int32 GetAttackDamage() const
	{
		return AttackDamage;
	}
	void SetAttackDamage(int32 da)
	{
		AttackDamage = da;
	}
	void Init();
	void Reset();
};
