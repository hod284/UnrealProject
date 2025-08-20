// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MonsterPawnMovement.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UMonsterPawnMovement : public UFloatingPawnMovement
{
	GENERATED_BODY()
protected:
	bool	mApplyGravity = true;
	// 중력 값.
	float	mGravity = 980.f;

	// 중력이 적용될 방향.
	FVector	mGravityDir;

	// AI의 이동 방향을 저장할 벡터.
	FVector	mAIMoveDir;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
public:
	

	void ClearAIMoveDir();
	void ClearMovement();

	UMonsterPawnMovement();
};
