// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../Widget/PlayMainUI.h"
#include "../Widget/IntroMainUI.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UImanager.generated.h"

/**
 메인 위젯들을 관리하는 싱글톤 클래스입니다.
 */
UCLASS()
class MYPRO_API UUImanager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TSubclassOf<UPlayMainUI> PlayMainUI; // 플레이 메인 UI
	UPROPERTY()
	TSubclassOf<UIntroMainUI> IntroMainUI; // 인트로 메인 UI

	
	UUImanager();
};
