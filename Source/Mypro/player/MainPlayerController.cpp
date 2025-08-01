// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

AMainPlayerController::AMainPlayerController()
{
	// tick�� Ȱ��ȭ �ϱ����� ��
	// ���� tick�� ��Ȱ��ȭ �ϰ� ������ �ּ�ó���� �ϸ� �ȴ�.
	PrimaryActorTick.bCanEverTick = true;

}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// ���콺 Ŀ�� ���̱�
	bShowMouseCursor = GetWorld()->GetGameInstance() ->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Intro ? true : false;
	// Ŭ���̾�Ʈ Ȯ��
	if (IsLocalController())
	{
		if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Intro)
		{
			 GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget()->AddToViewport();
		}
		
	}
}


