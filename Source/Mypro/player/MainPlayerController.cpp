// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

AMainPlayerController::AMainPlayerController()
{
	// tick를 활성화 하기위한 줄
	// 만약 tick를 비활성화 하고 싶으면 주석처릴를 하면 된다.
	PrimaryActorTick.bCanEverTick = true;

}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// 마우스 커서 보이기
	bShowMouseCursor = GetWorld()->GetGameInstance() ->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Intro ? true : false;
	// 클라이언트 확인
	if (IsLocalController())
	{
		if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Intro)
		{
			 GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget()->AddToViewport();
		}
		
	}
}


