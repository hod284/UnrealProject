// Fill out your copyright notice in the Description page of Project Settings.


#include "Intro.h"
// �����ѵ� ���� �����Ҷ� ���̴� ������ ���� ��ũ��
//IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, Mypro, "Mypro");

void AIntro::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetGameState(NowGameState::Intro);
}

AIntro::AIntro()
{
	
	PlayerControllerClass = AMainPlayerController::StaticClass();

}
