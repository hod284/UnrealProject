// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Gameinfo.h"
#include "GameFramework/Actor.h"
#include "Skill4_Magition.generated.h"

UCLASS()
class MYPRO_API ASkill4_Magition : public AActor
{
	GENERATED_BODY()
	
protected:
	FTimerHandle Time;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UNiagaraComponent> NiagaraParticle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UCapsuleComponent> BoxColider;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 AttackDamage;
	// �浹
	UFUNCTION()
	void OnHit_Skil4_Magition(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);
	// ������
	UFUNCTION()
	void OnCapsuleBeginOverlap_Skil4_Magition(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	// ������ ��
	UFUNCTION()
	void OnCapsuleEndOverlap_Skil4_Magition(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
	// Sets default values for this actor's properties
	ASkill4_Magition();
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
	void SetAttackDamage(FString cporfile)
	{
		BoxColider->SetCollisionProfileName(FName(*cporfile));
	}
};
