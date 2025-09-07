// Fill out your copyright notice in the Description page of Project Settings.


#include "PvPMode.h"

APvPMode::APvPMode()
{
	DefaultPawnClass = ASpectatorPawn::StaticClass();
	PlayerControllerClass = AMainPlayerController::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
}
void APvPMode::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetGameState(NowGameState::pvp);
}

void APvPMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	// defaultpawn�� �⺻������ �����Ǵµ� ���ʹ� �̰��� Ÿ���� ��� ��찡 ���� ���� �׸���  defalutpawn�� ��ó�� �ۿ��Ͽ� �����̴µ� ���صǾ 
	// defaultpawn ���� ������ ���� ���� ������� �����Ǵ°Ŵϱ� �÷��̾�� �õ������� ������ ���� ĳ���͸� �����ؼ� �����ϴ°Ŷ� �ʷ� ����
	if (APawn* Old = NewPlayer->GetPawn())
		Old->Destroy();
	// �÷��̾� ��Ʈ�ѷ� ĳ����
	if (!NewPlayer)
		return;
	AMainPlayerController* MyPC = Cast<AMainPlayerController>(NewPlayer);
	// Ŭ���̾�Ʈ�� ������ ĳ���� ���� �޾ƿ���
	TSubclassOf<APawn> SelectedCharacterClass = MyPC->GetSelectCharactertClass();

	// ĳ���� ���� �� Possess
	FVector SpawnLocation = FVector(20, 1030, 90);
	FRotator SpawnRotation = FRotator(0, -90, 0);
	APawn* NewPawn = GetWorld()->SpawnActor<APawn>(SelectedCharacterClass, SpawnLocation, SpawnRotation);
	MyPC->Possess(NewPawn);

}
