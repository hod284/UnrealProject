// Fill out your copyright notice in the Description page of Project Settings.


#include "InputManager.h"

UInputManager::UInputManager()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>
		InputContext(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/input/Contorller.Contorller'"));

	Context = InputContext.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		Move_A(TEXT("/Script/EnhancedInput.InputAction'/Game/input/move.move'"));

	Move = Move_A.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction>
		back_A(TEXT("/Script/EnhancedInput.InputAction'/Game/input/Back.Back'"));

	Back = back_A.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		Skill_A(TEXT("/Script/EnhancedInput.InputAction'/Game/input/Skill1.Skill1'"));

    Skill1  = Skill_A.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction>
		Skill_B(TEXT("/Script/EnhancedInput.InputAction'/Game/input/Skill2.Skill2'"));

	Skill2 = Skill_B.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction>
		Skill_C(TEXT("/Script/EnhancedInput.InputAction'/Game/input/Skill3.Skill3'"));

	Skill3 = Skill_C.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction>
		Skill_D(TEXT("/Script/EnhancedInput.InputAction'/Game/input/Skill4.Skill4'"));

	Skill4 = Skill_D.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction>
		Attack_A(TEXT("/Script/EnhancedInput.InputAction'/Game/input/attack.attack'"));

	Attack = Attack_A.Object;

}
