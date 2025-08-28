// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Gameinfo.h"
#include "GameFramework/Actor.h"
#include "Skill2_Magition.generated.h"

UCLASS()
class MYPRO_API ASkill2_Magition : public AActor
{
	GENERATED_BODY()
	
protected:
	// Sets default values for this actor's properties
	ASkill2_Magition();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UNiagaraComponent> NiagaraParticle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<USphereComponent> BoxColider;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<USplineComponent> Spline;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UProjectileMovementComponent> Movement;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AttAckDamage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector TargetLocation;
	// Ãæµ¹
	UFUNCTION()
	void OnHit_Skil2_Magition(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);
	// ¿À¹ö·¦
	UFUNCTION()
	void OnCapsuleBeginOverlap_Skil2_Magition(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	// ¿À¹ö·¦ ³¡
	UFUNCTION()
	void OnCapsuleEndOverlap_Skil2_Magition(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void ProjectileStop(const FHitResult & rersult);
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
	void SetTagetLocation(FVector ta)
	{
		TargetLocation = ta;
	}
};
