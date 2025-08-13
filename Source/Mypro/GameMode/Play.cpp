// Fill out your copyright notice in the Description page of Project Settings.


#include "Play.h"

APlay::APlay()
{
	DefaultPawnClass = AMyCharacter::StaticClass();
	PlayerControllerClass = AMainPlayerController::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();

}
void APlay::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetGameState(NowGameState::playgame);
}

void APlay::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	// 플레이어 컨트롤러 캐스팅
	if (!NewPlayer) 
		return;
	AMainPlayerController* MyPC = Cast<AMainPlayerController>(NewPlayer);
    // 클라이언트가 선택한 캐릭터 정보 받아오기
	TSubclassOf<APawn> SelectedCharacterClass = MyPC->GetSelectCharactertClass();

    // 캐릭터 생성 및 Possess
    FVector SpawnLocation = FVector(310,-60,88);
    FRotator SpawnRotation = FRotator::ZeroRotator;
    APawn* NewPawn = GetWorld()->SpawnActor<APawn>(SelectedCharacterClass, SpawnLocation, SpawnRotation);
    MyPC->Possess(NewPawn);

}
