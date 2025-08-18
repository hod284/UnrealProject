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
	OnMontageEnded.AddDynamic(this, &UMyPlayerAnimInstance::Attackend);
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
	if (!IsValid(AttackUpMontage))
		return;
	if (!Montage_IsPlaying(AttackMontage)&& AttackSectionIndex< AttackSectionArray.Num())
	{
		// 몽타주를 재생시킨다.
		Montage_Play(AttackMontage);
		Montage_JumpToSection(AttackSectionArray[AttackSectionIndex], AttackMontage);
		UE_LOG(LogMypro, Warning, TEXT("%d"), AttackSectionIndex);
		AttackSectionIndex += 1;
	}
}

void UMyPlayerAnimInstance::PlayBack()
{
	if (!IsValid(BackMontage))
		return;
	if (!Montage_IsPlaying(BackMontage))
	{
		// 몽타주를 재생시킨다.
		Montage_Play(BackMontage);
	}
}

void UMyPlayerAnimInstance::PlaySkill(int32 index)
{
	if (!IsValid(SkillMontage))
		return;
	if (!Montage_IsPlaying(SkillMontage))
	{
		UE_LOG(LogMypro, Warning, TEXT("%d"),index);
		// 몽타주를 재생시킨다.
		Montage_Play(SkillMontage,1.0f);
		Montage_JumpToSection(SkillSectionArray[index], SkillMontage);
		Montage_SetNextSection(SkillSectionArray[index],FName(""));
	}
}

void UMyPlayerAnimInstance::Attackend(UAnimMontage* Montage, bool Interrupted)
{
	if (AttackMontage == Montage)
	{
		if(!Interrupted)
		AttackSectionIndex = 0;
	}
}

void UMyPlayerAnimInstance::AnimNotify_Attack()
{
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
