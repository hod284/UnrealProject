// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerAnimInstance.h"

void UMyPlayerAnimInstance::PostInitProperties()
{
	Super::PostInitProperties();
}

void UMyPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UMyPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UMyPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

}

void UMyPlayerAnimInstance::PlayAttack()
{
}

void UMyPlayerAnimInstance::PlaySkill(int32 index)
{
}

void UMyPlayerAnimInstance::AnimNotify_Attack()
{
}

void UMyPlayerAnimInstance::AnimNotify_AttackCombo()
{
	CanCombo = true;
}

void UMyPlayerAnimInstance::AnimNotify_Skill1Play()
{

}

void UMyPlayerAnimInstance::AnimNotify_Skill2Play()
{

}

void UMyPlayerAnimInstance::AnimNotify_Skill3Play()
{

}

void UMyPlayerAnimInstance::AnimNotify_Skill4Play()
{

}
