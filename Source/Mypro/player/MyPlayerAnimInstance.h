// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "Animation/AnimInstance.h"
#include "MyPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UMyPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		MoveSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		Dir;
	bool		CanCombo;
	//UObject ��� Ŭ������ �ʱ�ȭ �ܰ� �� �ϳ���,��ü�� ������Ƽ�� �����ڳ� �⺻�� ���� ���Ŀ� �޸𸮿� ������ ���õ� ���� ȣ��Ǵ� ���� �Լ��Դϴ�.
	virtual void PostInitProperties() override;
	virtual void NativeBeginPlay() override;
	//�ִϸ��̼� �������Ʈ �ʱ�ȭ�� C++ �������̵� �Լ�
	virtual void NativeInitializeAnimation() override;
	// ���� �����忡�� ȣ��.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
public:
	void PlayAttack();
	void PlaySkill(int32 index);
	UFUNCTION()
	void AnimNotify_Attack();
	UFUNCTION()
	void AnimNotify_AttackCombo();
	UFUNCTION()
	void AnimNotify_Skill1Play();
	UFUNCTION()
	void AnimNotify_Skill2Play();
	UFUNCTION()
	void AnimNotify_Skill3Play();
	UFUNCTION()
	void AnimNotify_Skill4Play();
};
