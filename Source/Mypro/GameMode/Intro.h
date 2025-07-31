// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include  "../player/MainPlayerController.h"
#include  "../singleton/GameManager.h"
#include "GameFramework/GameModeBase.h"
#include "Intro.generated.h"

/**
 인트로 레벨에서 쓰이는 게임 모드 클래스
 */
UCLASS()
class MYPRO_API AIntro : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// override는 부모클래스의 함수를 재정의한다고 컴파일러에게 명확히 알려준다.
	virtual void BeginPlay() override;
	AIntro();
};
