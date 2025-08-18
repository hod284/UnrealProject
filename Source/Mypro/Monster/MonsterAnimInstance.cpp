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
	MontageMap = AnimInfo->MontageMap;
	AttackMontage = *MontageMap.Find(TEXT("At1"));
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


void UMonsterAnimInstance::MonsterAttackend(UAnimMontage* Montage, bool Interrupted)
{
}


void UMonsterAnimInstance::MonsterAttack1()
{
	if (IsValid(AttackMontage))
		return;
	if (!Montage_IsPlaying(AttackMontage))
		Montage_Play(AttackMontage);
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
void UMonsterAnimInstance::AnimNotify_At1Play()
{
}

void UMonsterAnimInstance::AnimNotify_At2Play()
{
}

void UMonsterAnimInstance::AnimNotify_At3Play()
{
}

void UMonsterAnimInstance::AnimNotify_At4Play()
{
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
		}

	}
}
