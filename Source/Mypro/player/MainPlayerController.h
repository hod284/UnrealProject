// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../singleton/GameManager.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 클라이언트 플레이어 컨트롤러 클래스입니다.
 여기서 인트로 위젯클래스를 뷰포트에 추가하는 이유는 서버와 통신없이 클라이언트만 보이게 하기 위합입니다
 게임모드는 서버와 통신을 하기 때문에 서버와 통신이 일어나면 인트로 위젯이 클라이언트쪽에 안보이게 될수 있어서 여기에 인트로 위젯을 생성및 뷰포트에 추가합니다
 케릭터 컨트롤러 생성순서
 gameinstance ->gamesubinstance ->levelload -> gamemode ->playercontroller ->charactercontroller
 */
UCLASS()
class MYPRO_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	
	TSubclassOf<UUserWidget> MainWidgetBluprinte; // 레벨에 메인으로 걸리는 위젯 블루프린트입니다.
	TObjectPtr<UUserWidget> MainWidget; // 레벨에 메인으로 걸리는 위젯입니다.
	AMainPlayerController();// 생성자
	// override는 부모클래스의 함수를 재정의한다고 컴파일러에게 명확히 알려준다.
	virtual void BeginPlay() override;
};
