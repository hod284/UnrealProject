// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../common/AnimationObject.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TMap<FName, TObjectPtr<UAnimSequence>> SequenceMap;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TMap<FName, TObjectPtr<UAnimMontage>>	MontageMap;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage>	AttackMontage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMonsterDefaultAnim	mAnimType = EMonsterDefaultAnim::Idle;

	//UObject ��� Ŭ������ �ʱ�ȭ �ܰ� �� �ϳ���,��ü�� ������Ƽ�� �����ڳ� �⺻�� ���� ���Ŀ� �޸𸮿� ������ ���õ� ���� ȣ��Ǵ� ���� �Լ��Դϴ�.
	virtual void PostInitProperties() override;
	virtual void NativeBeginPlay() override;
	//�ִϸ��̼� �������Ʈ �ʱ�ȭ�� C++ �������̵� �Լ�
	virtual void NativeInitializeAnimation() override;
	// ���� �����忡�� ȣ��.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


public:
	void MonsterAttack1();
	void MonsterAttack2();
	void MonsterAttack3();
	void MonsterAttack4();
	void DeathAni();
	void StunAni();

	UFUNCTION()
	void MonsterAttackend(UAnimMontage* Montage, bool Interrupted);
	UFUNCTION()
	void AnimNotify_At1Play();
	UFUNCTION()
	void AnimNotify_At2Play();
	UFUNCTION()
	void AnimNotify_At3Play();
	UFUNCTION()
	void AnimNotify_At4Play();
	UFUNCTION()
	void AnimNotify_Death();
};
