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
	int32 AttackDamage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent* UScene;

	float TravelSpeed = 1200.f;    
	float HomingAccelMag = 6000.f; 
	bool bLoop = false;            
	bool bPingPong = false;        
	float StartDistance = 0.f;     
	bool bDisableGravity = true;   
	float Elapsed;
	float AccelRampTime = 0.6f;   
	float StartAccel = 800.f;    
	float EndAccel = 8000.f;    
	// �浹
	UFUNCTION()
	void OnHit_Skil2_Magition(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);
	// ������
	UFUNCTION()
	void OnCapsuleBeginOverlap_Skil2_Magition(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	// ������ ��
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
	void ApplyInitialSideKick(); 
	void UpdateAccel(float dt); 
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
	void SetTagetTransform(USceneComponent *ta)
	{
		UScene = ta;
	}
	void SetAttackDamage(FString cporfile)
	{
		BoxColider->SetCollisionProfileName(FName(*cporfile));
	}
};
