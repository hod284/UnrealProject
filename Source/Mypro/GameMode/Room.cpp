// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"

void ARoom::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetGameState(NowGameState::Room);
}

ARoom::ARoom()
{
	DefaultPawnClass = NULL;
	SpectatorClass = NULL;
	PlayerControllerClass = AMainPlayerController::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
}

void ARoom::PostLogin(APlayerController* NewPlayer)
{
	if (APawn* Old = NewPlayer->GetPawn())
		Old->Destroy();
}
