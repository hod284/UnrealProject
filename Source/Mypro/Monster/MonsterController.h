// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "AIController.h"
#include "MonsterController.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API AMonsterController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAIPerceptionComponent>	AIPerception;

	TObjectPtr<UAISenseConfig_Sight>	SightConfig;
	TObjectPtr<UAISenseConfig_Damage>	DamageConfig;
	AMonsterController();
	float DetectiveRange =1500.0f;
public:
	virtual void OnConstruction(const FTransform& Transform) override;

	// �̵��� �Ϸ�� �Ŀ� ȣ��Ǵ� �Լ�.
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const;

	UFUNCTION()
	void OnTargetmethod(AActor* Target, FAIStimulus Stimulus);
	

	
};
