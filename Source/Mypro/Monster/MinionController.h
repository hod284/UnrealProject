// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "MonsterPawnMovement.h"
#include "AIController.h"
#include "MinionController.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API AMinionController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAIPerceptionComponent>	AIPerception;

	TObjectPtr<UAISenseConfig_Sight>	SightConfig;
	TObjectPtr<UAISenseConfig_Damage>	DamageConfig;
	AMinionController();
	float DetectiveRange = 3000.0f;
	AActor* TargetActor;
	TArray<AActor*> PerceivedActors;
	virtual void Tick(float DeltaTime) override;
public:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const;

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PlayAttack(UAnimSequence*ani);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_Run(UAnimSequence*ani);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_Death(UAnimSequence*ani);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_idle(UAnimSequence*ani);

	void Idle_M();
	void Attack_M();
	void Death_M();
	void Run_M();
	virtual void StopMovement() override;
	void ClearMovment();

	AActor* GetTarget()
	{
		return TargetActor;
	}
};
