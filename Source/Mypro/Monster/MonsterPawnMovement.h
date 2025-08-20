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
	// �߷� ��.
	float	mGravity = 980.f;

	// �߷��� ����� ����.
	FVector	mGravityDir;

	// AI�� �̵� ������ ������ ����.
	FVector	mAIMoveDir;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
public:
	

	void ClearAIMoveDir();
	void ClearMovement();

	UMonsterPawnMovement();
};
