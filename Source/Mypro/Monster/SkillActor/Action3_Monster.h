// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Gameinfo.h"
#include "GameFramework/Actor.h"
#include "Action3_Monster.generated.h"

UCLASS()
class MYPRO_API AAction3_Monster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAction3_Monster();

protected:
	FTimerHandle Time;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UNiagaraComponent> NiagaraParticle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UCapsuleComponent> BoxColider;
	float AttAckDamage;
	// Ãæµ¹
	UFUNCTION()
	void OnHit_Action3_M(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);
	// ¿À¹ö·¦
	UFUNCTION()
	void OnCapsuleBeginOverlap_Action3_M(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	// ¿À¹ö·¦ ³¡
	UFUNCTION()
	void OnCapsuleEndOverlap_Action3_M(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float GetAttAckDamage() const
	{
		return AttAckDamage;
	}
	void SetAttAckDamage(float da)
	{
		AttAckDamage = da;
	}
};
