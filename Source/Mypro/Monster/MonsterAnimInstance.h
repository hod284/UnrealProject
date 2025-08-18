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

	//UObject 기반 클래스의 초기화 단계 중 하나로,객체의 프로퍼티가 생성자나 기본값 복사 이후에 메모리에 완전히 세팅된 직후 호출되는 가상 함수입니다.
	virtual void PostInitProperties() override;
	virtual void NativeBeginPlay() override;
	//애니메이션 블루프린트 초기화용 C++ 오버라이드 함수
	virtual void NativeInitializeAnimation() override;
	// 게임 스레드에서 호출.
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
