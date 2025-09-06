// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../common/AnimationObject.h"
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

	int32		AttackSectionIndex = 0;
	const FPlayerAnimInfo* AnimInfo;

	virtual void PostInitProperties() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeInitializeAnimation() override;
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
	void Attackend(UAnimMontage* Montage, bool Interrupted);
	UFUNCTION()
	void AnimNotify_Attack();
	UFUNCTION()
	void AnimNotify_Skill1Play();
	UFUNCTION()
	void AnimNotify_Skill2Play();
	UFUNCTION()
	void AnimNotify_Skill3Play();
	UFUNCTION()
	void AnimNotify_Skill4Play();
	void AniInite();
	UFUNCTION()
	void AnimNotify_AttackArrayReset();
};
