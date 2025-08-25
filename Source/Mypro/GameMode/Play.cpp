// Fill out your copyright notice in the Description page of Project Settings.


#include "Play.h"

APlay::APlay()
{
	DefaultPawnClass = ASpectatorPawn::StaticClass();
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
	// defaultpawn이 기본적으로 생성되는데 몬스터는 이것을 타겟을 잡는 경우가 종종 있음 그리고  defalutpawn이 턱처럼 작용하여 움직이는데 방해되어서 
	// defaultpawn 으로 생성된 폰을 삭제 가장먼저 생성되는거니까 플레이어에서 올드폰으로 잡을수 있음 캐릭터를 생성해서 빙의하는거라 필료 없음
	if (APawn* Old = NewPlayer->GetPawn())
		Old->Destroy();
	// 플레이어 컨트롤러 캐스팅
	if (!NewPlayer) 
		return;
	AMainPlayerController* MyPC = Cast<AMainPlayerController>(NewPlayer);
    // 클라이언트가 선택한 캐릭터 정보 받아오기
	TSubclassOf<APawn> SelectedCharacterClass = MyPC->GetSelectCharactertClass();

    // 캐릭터 생성 및 Possess
    FVector SpawnLocation = FVector(20,1030,90);
    FRotator SpawnRotation = FRotator(0,-90,0);
    APawn* NewPawn = GetWorld()->SpawnActor<APawn>(SelectedCharacterClass, SpawnLocation, SpawnRotation);
    MyPC->Possess(NewPawn);

}
