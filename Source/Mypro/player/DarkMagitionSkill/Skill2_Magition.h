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
	TObjectPtr<UProjectileMovementComponent> Movement;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AttAckDamage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent* UScene;

	float TravelSpeed = 1200.f;          // cm/s (스플라인 따라 이동 속도)
	float HomingAccelMag = 6000.f;       // 유도 가속 크기(커브가 급하면 올려줘)
	bool bLoop = false;                  // 끝나면 다시 처음으로
	bool bPingPong = false;              // 왕복
	float StartDistance = 0.f;           // 시작 지점(cm)
	bool bDisableGravity = true;         // 곡선 연출엔 보통 중력 끔
	float Elapsed;
	float AccelRampTime = 0.6f;   // 가속을 Start→End로 올리는 시간(sec)
	float StartAccel = 800.f;     // 시작 유도가속(크면 곡선이 덜 커짐)
	float EndAccel = 8000.f;    // 막판 유도가속(크면 강하게 빨라붙음)
	// 충돌
	UFUNCTION()
	void OnHit_Skil2_Magition(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);
	// 오버랩
	UFUNCTION()
	void OnCapsuleBeginOverlap_Skil2_Magition(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	// 오버랩 끝
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
	void ApplyInitialSideKick(); // 처음에 옆으로 틀어 쏘기
	void UpdateAccel(float dt);  // 유도 가속 램프업
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
	void SetTagetTransform(USceneComponent *ta)
	{
		UScene = ta;
	}
};
