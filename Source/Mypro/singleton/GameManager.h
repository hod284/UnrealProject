// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManager.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UGameManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
private:
	// 게임 메니저에서 게임 스테이트 설정
	NowGameState  state = NowGameState ::None;
public:
	// 기본 생성자
	// 생성자에 초기화하지 않겠다는뜻
	UGameManager() =default;

	void SetGameState(NowGameState newState) {
		state = newState; 
	}
	NowGameState GetGameState() const { 
		return state; 
	}
};
