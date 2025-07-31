// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../Widget/PlayMainUI.h"
#include "../Widget/IntroMainUI.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UImanager.generated.h"

/**
 ���� �������� �����ϴ� �̱��� Ŭ�����Դϴ�.
 */
UCLASS()
class MYPRO_API UUImanager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TSubclassOf<UPlayMainUI> PlayMainUI; // �÷��� ���� UI
	UPROPERTY()
	TSubclassOf<UIntroMainUI> IntroMainUI; // ��Ʈ�� ���� UI

	
	UUImanager();
};
