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

	// AI�� �̵��ϴ� �⺻ �̵� ������ �����.
	FVector	MoveVelocity = mAIMoveDir * MaxSpeed;


	// �߷��� �����ؾ� �ϴ� ���
	if (mApplyGravity)
	{
		MoveVelocity += mGravityDir * mGravity;
	}

	
	// �̵��� ó���Ѵ�.
	FHitResult	Hit;
	SafeMoveUpdatedComponent(MoveVelocity * DeltaTime, UpdatedComponent->GetComponentRotation(), true, Hit);

	if (Hit.IsValidBlockingHit())
	{
		SlideAlongSurface(MoveVelocity * DeltaTime, 1.f - Hit.Time, Hit.Normal, Hit);
	}
	Velocity = MoveVelocity;
}

// AIController�� MoveToActor, MoveToLocation �Լ��� ���ο��� ȣ�����ִ� �Լ���
// UPathFollowingComponent�� FAIMoveRequest�� ó���ϴ� �� ��ǥ ��ġ������ ���� ������ ����ؼ�
// ȣ�����ش�.
void UMonsterPawnMovement::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// AI�� ��ã�⸦ ���� �̵��� ���������� ũ�Ⱑ 1�� �������ͷ� ���⸸ ���´�.
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
