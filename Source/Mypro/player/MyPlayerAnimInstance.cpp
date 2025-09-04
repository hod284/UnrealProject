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
		if (PlayerCharacter->GetBackMoving()|| PlayerCharacter->GetDashMoving())
		{
			MoveSpeed = 0;
		}
		else if (Movement)
		{
			MoveSpeed = Movement->Velocity.Size();
			
		}
	}
}

void UMyPlayerAnimInstance::PlayAttack()
{
	AMyCharacter* PlayerCharacter =	Cast<AMyCharacter>(TryGetPawnOwner());
	if (AttackSectionIndex >= AttackSectionArray.Num())
		AttackSectionIndex = 0;
	if (!PlayerCharacter->GetCanskill3() && IsValid(AttackUpMontage))
	{
		if (!Montage_IsPlaying(AttackUpMontage) && AttackSectionIndex < AttackSectionArray.Num())
		{
			// 몽타주를 재생시킨다.
			Montage_Play(AttackUpMontage);
			Montage_JumpToSection(AttackSectionArray[AttackSectionIndex], AttackUpMontage);
			AttackSectionIndex += 1;
		}
	}
	else
	{
		if (!IsValid(AttackMontage))
			return;
		if (!Montage_IsPlaying(AttackMontage) && AttackSectionIndex < AttackSectionArray.Num())
		{
			// 몽타주를 재생시킨다.
			Montage_Play(AttackMontage);
			Montage_JumpToSection(AttackSectionArray[AttackSectionIndex], AttackMontage);
			AttackSectionIndex += 1;
		}
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
	if (AttackUpMontage == Montage)
	{
		if (!Interrupted)
			AttackSectionIndex = 0;
	}
}
void UMyPlayerAnimInstance::AnimNotify_AttackArrayReset()
{
		AttackSectionIndex = 0;
}

void UMyPlayerAnimInstance::AnimNotify_Attack()
{
	AMyCharacter* ch = Cast<AMyCharacter>(TryGetPawnOwner());
	if (IsValid(ch))
		ch->NAttack();
}



void UMyPlayerAnimInstance::AnimNotify_Skill1Play()
{
	AMyCharacter* ch = Cast<AMyCharacter>(TryGetPawnOwner());
	if (IsValid(ch))
		ch->Skill1();
}

void UMyPlayerAnimInstance::AnimNotify_Skill2Play()
{
	AMyCharacter* ch = Cast<AMyCharacter>(TryGetPawnOwner());
	if (IsValid(ch))
		ch->Skill2();
}

void UMyPlayerAnimInstance::AnimNotify_Skill3Play()
{
	AMyCharacter* ch = Cast<AMyCharacter>(TryGetPawnOwner());
	if (IsValid(ch))
		ch->Skill3();
}

void UMyPlayerAnimInstance::AnimNotify_Skill4Play()
{
	AMyCharacter* ch = Cast<AMyCharacter>(TryGetPawnOwner());
	if (IsValid(ch))
		ch->Skill4();
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
				AttackUpMontage = *MontageMap.Find(TEXT("AtttackUp"));
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
