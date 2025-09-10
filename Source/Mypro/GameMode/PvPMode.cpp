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
	if (APawn* Old = NewPlayer->GetPawn())
		Old->Destroy();
	RestartPlayer(NewPlayer);
}
void APvPMode::RestartPlayer(AController* NewPlayer)
{
	int32 PlayerCount = GetNumPlayers();
	FVector SpawnLocation;
	FRotator SpawnRotation;
	FVector Scale = FVector(1, 1, 1);
	TSubclassOf<APawn> ch;
	if (PlayerCount ==1)
	{
	   SpawnLocation = FVector(110,690, 95);
	   SpawnRotation = FRotator(0, -90, 0);
	   AMainPlayerController* MyPC = Cast<AMainPlayerController>(NewPlayer);
	   ch= MyPC->GetSelectCharactertClass();
	}
	else
	{
		SpawnLocation = FVector(110, -670, 95);
		SpawnRotation = FRotator(0, 90, 0);
		ch = GetDefaultPawnClassForController(NewPlayer);
	}
	FTransform T(SpawnRotation, SpawnLocation, Scale);
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	APawn* po = GetWorld()->SpawnActor<APawn>(ch, T, Params);
	if (po)
		NewPlayer->Possess(po);
}

UClass* APvPMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (AMyPlayerState* ps = InController->GetPlayerState<AMyPlayerState>())
	{
		if (ps->SelectCharacter_C)
			return ps->SelectCharacter_C;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}


