// Fill out your copyright notice in the Description page of Project Settings.


#include "Intro.h"
// ����ѵ� ���� �����Ҷ� ���̴� ������ ���� ��ũ��
//IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, Mypro, "Mypro");

void AIntro::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetGameState(NowGameState::Intro);
	GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget()->AddToViewport();
	if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
	{
		Settings->SetScreenResolution(FIntPoint(1920, 1080));
		Settings->ApplySettings(true);
	}
}

AIntro::AIntro()
{
	
	PlayerControllerClass = AMainPlayerController::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
}
