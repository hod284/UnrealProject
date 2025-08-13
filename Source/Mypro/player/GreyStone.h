// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyCharacter.h"
#include "GreyStone.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API AGreyStone : public AMyCharacter
{
	GENERATED_BODY()
public:
	virtual void NAttack() override;
	virtual void  Skill1() override;
	virtual void  Skill2()override;
	virtual void  Skill3()override;
	virtual void  Skill4()override;

	AGreyStone();
};
