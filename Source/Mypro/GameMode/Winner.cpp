// Fill out your copyright notice in the Description page of Project Settings.


#include "Winner.h"

void AWinner::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetGameState(NowGameState::gameover);
}

AWinner::AWinner()
{
	DefaultPawnClass = NULL;
	SpectatorClass = NULL;
	PlayerControllerClass = AMainPlayerController::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
}

void AWinner::PostLogin(APlayerController* NewPlayer)
{
	if (APawn* Old = NewPlayer->GetPawn())
		Old->Destroy();
}