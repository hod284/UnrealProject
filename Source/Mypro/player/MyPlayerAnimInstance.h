// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../common/AnimationObject.h"
#include "../singleton/DataManager.h"
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

	UPROPERTY(EditAnywhere)
	Characters Ch =Characters::None;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		MoveSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		Direction; 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FName>	AttackSectionArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FName>	SkillSectionArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TMap<FName, TObjectPtr<UBlendSpace>>	BlendSpaceMap;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TMap<FName, TObjectPtr<UAnimMontage>>   MontageMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage>	SkillMontage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage>	AttackMontage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage>	AttackUpMontage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage>	BackMontage;
	// ���� � ������ �����ϰ� �ִ��� ������ �ε���.
	int32		AttackSectionIndex = 0;
	// ���� ������ �Ǵ��Ѵ�.
	bool		mAttackEnable = false;
	const FPlayerAnimInfo* AnimInfo;
	// ���� ������ �Ǵ��Ѵ� �޺� ���� �Ǵ�
	bool		CanCombo;
	//UObject ��� Ŭ������ �ʱ�ȭ �ܰ� �� �ϳ���,��ü�� ������Ƽ�� �����ڳ� �⺻�� ���� ���Ŀ� �޸𸮿� ������ ���õ� ���� ȣ��Ǵ� ���� �Լ��Դϴ�.
	virtual void PostInitProperties() override;
	virtual void NativeBeginPlay() override;
	//�ִϸ��̼� �������Ʈ �ʱ�ȭ�� C++ �������̵� �Լ�
	virtual void NativeInitializeAnimation() override;
	// ���� �����忡�� ȣ��.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
public:
	void SetDir(float Dir)
	{
		Direction = Dir;
	}
	void PlayAttack();
	void PlayBack();
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
	void AniInite();
};
