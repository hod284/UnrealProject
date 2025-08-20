// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPawnMovement.h"

UMonsterPawnMovement::UMonsterPawnMovement()
{
	PrimaryComponentTick.bCanEverTick = true;

	mGravityDir = FVector(0.0, 0.0, -1.0);
	mGravity = 980.f;
	mApplyGravity = true;
	mAIMoveDir = FVector::ZeroVector;
}
void UMonsterPawnMovement::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent)
	{
	 	return;
	}

	// AI가 이동하는 기본 이동 방향을 만든다.
	FVector	MoveVelocity = mAIMoveDir * MaxSpeed;


	// 중력을 적용해야 하는 경우
	if (mApplyGravity)
	{
		MoveVelocity += mGravityDir * mGravity;
	}

	
	// 이동을 처리한다.
	FHitResult	Hit;
	SafeMoveUpdatedComponent(MoveVelocity * DeltaTime, UpdatedComponent->GetComponentRotation(), true, Hit);

	if (Hit.IsValidBlockingHit())
	{
		SlideAlongSurface(MoveVelocity * DeltaTime, 1.f - Hit.Time, Hit.Normal, Hit);
	}
	Velocity = MoveVelocity;
}

// AIController의 MoveToActor, MoveToLocation 함수가 내부에서 호출해주는 함수로
// UPathFollowingComponent가 FAIMoveRequest를 처리하는 중 목표 위치까지의 직선 방향을 계산해서
// 호출해준다.
void UMonsterPawnMovement::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// AI가 길찾기를 통해 이동할 직선방향을 크기가 1인 단위벡터로 방향만 얻어온다.
	mAIMoveDir = MoveVelocity.GetSafeNormal();
}


void UMonsterPawnMovement::ClearMovement()
{
	mAIMoveDir = FVector::ZeroVector;
	mApplyGravity = false;
}
void  UMonsterPawnMovement::ClearAIMoveDir()
{
	mAIMoveDir = FVector::ZeroVector;
}
