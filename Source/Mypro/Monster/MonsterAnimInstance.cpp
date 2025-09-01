// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "Monster.h"
void UMonsterAnimInstance::PostInitProperties()
{
	Super::PostInitProperties();
	// Initialize any properties or variables here
	const  UAnimationObject* DataSystem = GetDefault<UAnimationObject>();
	const FMonsterAnimInfo* AnimInfo = DataSystem->GetDataAnimainfo_Monster();
	SequenceMap = AnimInfo->SequenceMap;
}

void UMonsterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UMonsterAnimInstance::MonsterAttack1()
{
	mAnimType = EMonsterDefaultAnim::Attack1;
}

void UMonsterAnimInstance::MonsterAttack2()
{
	mAnimType = EMonsterDefaultAnim::Attack2;
}
void UMonsterAnimInstance::MonsterAttack3()
{
	mAnimType = EMonsterDefaultAnim::Attack3;
}
void UMonsterAnimInstance::MonsterAttack4()
{
	mAnimType = EMonsterDefaultAnim::Attack4;
}
void UMonsterAnimInstance::DeathAni()
{
	mAnimType = EMonsterDefaultAnim::Death;
}
void UMonsterAnimInstance::StunAni()
{
	mAnimType = EMonsterDefaultAnim::Stun;
}
void UMonsterAnimInstance::RubAni()
{
	mAnimType = EMonsterDefaultAnim::Run;
}
void UMonsterAnimInstance::IdleAni()
{
	mAnimType = EMonsterDefaultAnim::Idle;
}
void UMonsterAnimInstance::AnimNotify_At1Play()
{
	AMonster* monster = Cast<AMonster>(TryGetPawnOwner());
	monster->Attack1();
}

void UMonsterAnimInstance::AnimNotify_At2Play()
{
	AMonster* monster = Cast<AMonster>(TryGetPawnOwner());
	monster->Attack2();
}

void UMonsterAnimInstance::AnimNotify_At3Play()
{
	AMonster* monster = Cast<AMonster>(TryGetPawnOwner());
	monster->Attack3();
}

void UMonsterAnimInstance::AnimNotify_At4Play()
{
	AMonster* monster = Cast<AMonster>(TryGetPawnOwner());
	monster->Attack4();
}
void UMonsterAnimInstance::AnimNotify_At2Reset()
{
	AMonster* monster = Cast<AMonster>(TryGetPawnOwner());
	monster->GetAAction2_Monster()->Reset();
}
void UMonsterAnimInstance::AnimNotify_At3Reset()
{
	AMonster* monster = Cast<AMonster>(TryGetPawnOwner());
	monster->GetAAction3_Monster()->Reset();
}
void UMonsterAnimInstance::AnimNotify_At4Reset()
{
	AMonster* monster = Cast<AMonster>(TryGetPawnOwner());
	monster->GetAAction4_Monster()->Reset();
}

void UMonsterAnimInstance::AnimNotify_Death()
{
}
void UMonsterAnimInstance::AnimNotify_AtEnd()
{
	AMonster* monster = Cast<AMonster>(TryGetPawnOwner());
	if (monster)
	{
		AAIController* AIController = Cast<AAIController>(monster->GetController());
		if (AIController)
		{
				AIController->GetBlackboardComponent()->SetValueAsBool(TEXT("AttackEnd"), true);
				IdleAni();
		}

	}
}
