// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerAnimInstance.h"
#include "MyCharacter.h"
void UMyPlayerAnimInstance::PostInitProperties()
{
	Super::PostInitProperties();
	AniInite();
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
	AMyCharacter * PlayerCharacter =
		Cast<AMyCharacter>(TryGetPawnOwner());

	// 얻어온 객체가 유효하다면.
	if (IsValid(PlayerCharacter))
	{
		UCharacterMovementComponent* Movement =
			PlayerCharacter->GetCharacterMovement();

		if (Movement)
		{
			MoveSpeed = Movement->Velocity.Size();
			
		}
	}
}

void UMyPlayerAnimInstance::PlayAttack()
{
}

void UMyPlayerAnimInstance::PlayBack()
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

void UMyPlayerAnimInstance::AniInite()
{
	const  UAnimationObject* DataSystem = GetDefault<UAnimationObject>();
	if (DataSystem)
	{
		switch (Ch)
		{
		case Characters::Guiden:
			AnimInfo = DataSystem->GetAnimaDatainfo_G();
			if (AnimInfo)
			{
				BlendSpaceMap = AnimInfo->BlendSpaceMap;
				MontageMap = AnimInfo->MontageMap;
				AttackSectionArray = AnimInfo->AttackSectionArray;
				SkillSectionArray= AnimInfo->SkillSectionArray;
				AttackMontage = *MontageMap.Find(TEXT("Attack"));
				SkillMontage = *MontageMap.Find(TEXT("Skill"));
				BackMontage = *MontageMap.Find(TEXT("Back"));
				AttackUpMontage = nullptr;
			}
			break;
		case Characters::Warrior:
			AnimInfo = DataSystem->GetAnimaDatainfo_W();
			if (AnimInfo)
			{
				BlendSpaceMap = AnimInfo->BlendSpaceMap;
				MontageMap = AnimInfo->MontageMap;
				AttackSectionArray = AnimInfo->AttackSectionArray;
				SkillSectionArray = AnimInfo->SkillSectionArray;
				AttackMontage = *MontageMap.Find(TEXT("Attack"));
				SkillMontage = *MontageMap.Find(TEXT("Skill"));
				BackMontage = *MontageMap.Find(TEXT("Back"));
				AttackUpMontage = *MontageMap.Find(TEXT("AtttackUp"));
			}
			break;
		case Characters::DarkMagion:
			AnimInfo = DataSystem->GetAnimaDatainfo_D();
			if (AnimInfo)
			{
				BlendSpaceMap = AnimInfo->BlendSpaceMap;
				MontageMap = AnimInfo->MontageMap;
				AttackSectionArray = AnimInfo->AttackSectionArray;
				SkillSectionArray=AnimInfo->SkillSectionArray;
				AttackMontage = *MontageMap.Find(TEXT("Attack"));
				SkillMontage = *MontageMap.Find(TEXT("Skill"));
				BackMontage = *MontageMap.Find(TEXT("Back"));
				AttackUpMontage = nullptr;
			}
			break;
		}
	}
}
