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
	// 현재 어떤 섹션이 동작하고 있는지 저장할 인덱스.
	int32		AttackSectionIndex = 0;
	// 공격 중인지 판단한다.
	bool		mAttackEnable = false;
	const FPlayerAnimInfo* AnimInfo;
	// 공격 중인지 판단한다 콤보 할지 판단
	bool		CanCombo;
	//UObject 기반 클래스의 초기화 단계 중 하나로,객체의 프로퍼티가 생성자나 기본값 복사 이후에 메모리에 완전히 세팅된 직후 호출되는 가상 함수입니다.
	virtual void PostInitProperties() override;
	virtual void NativeBeginPlay() override;
	//애니메이션 블루프린트 초기화용 C++ 오버라이드 함수
	virtual void NativeInitializeAnimation() override;
	// 게임 스레드에서 호출.
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
