// Fill out your copyright notice in the Description page of Project Settings.


#include "Play.h"

APlay::APlay()
{

	PlayerControllerClass = AMainPlayerController::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();

}
void APlay::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetGameState(NowGameState::playgame);
}
