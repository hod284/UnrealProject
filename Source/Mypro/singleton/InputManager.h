// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InputManager.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UInputManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	TObjectPtr<UInputMappingContext>	Context;
	TObjectPtr<UInputAction>			Move;
	TObjectPtr<UInputAction>			Back;
	TObjectPtr<UInputAction>			Skill1;
	TObjectPtr<UInputAction>			Skill2;
	TObjectPtr<UInputAction>			Skill3;
	TObjectPtr<UInputAction>			Skill4;
	TObjectPtr<UInputAction>			Attack;
	UInputManager();
};
