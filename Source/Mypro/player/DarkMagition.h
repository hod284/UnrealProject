// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyCharacter.h"
#include "DarkMagitionSkill/Skill1_Magition.h"
#include "DarkMagitionSkill/Skill2_Magition.h"
#include "DarkMagitionSkill/Skill3_Magition.h"
#include "DarkMagitionSkill/Skill4_Magition.h"
#include "DarkMagitionSkill/SlashAttack_Magition.h"
#include "DarkMagition.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API ADarkMagition : public AMyCharacter
{
	GENERATED_BODY()
protected:
	const FCharacterInfo* Info;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sk")
	TSubclassOf<ASkill1_Magition> Sk1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sk")
	TSubclassOf<ASkill2_Magition> Sk2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sk")
	TSubclassOf<ASkill3_Magition> Sk3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sk")
	TSubclassOf<ASkill4_Magition> Sk4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sk")
	TSubclassOf<ASlashAttack_Magition > Attack;
	virtual void BeginPlay() override;
	int32 Atn = 0;
     
public:

	ADarkMagition();
	virtual void NAttack() override;
	virtual void  Skill1() override;
	virtual void  Skill2()override;
	virtual void  Skill3()override;
	virtual void  Skill4()override;
};
