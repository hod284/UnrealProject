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
	// �÷��̾� ��Ʈ�ѷ� ĳ����
	if (!NewPlayer) 
		return;
	AMainPlayerController* MyPC = Cast<AMainPlayerController>(NewPlayer);
    // Ŭ���̾�Ʈ�� ������ ĳ���� ���� �޾ƿ���
	TSubclassOf<APawn> SelectedCharacterClass = MyPC->GetSelectCharactertClass();

    // ĳ���� ���� �� Possess
    FVector SpawnLocation = FVector(310,-60,88);
    FRotator SpawnRotation = FRotator::ZeroRotator;
    APawn* NewPawn = GetWorld()->SpawnActor<APawn>(SelectedCharacterClass, SpawnLocation, SpawnRotation);
    MyPC->Possess(NewPawn);

}
