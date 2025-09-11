// Fill out your copyright notice in the Description page of Project Settings.


#include "PvPMode.h"
#include "../player/MyCharacter.h"
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
	TSubclassOf<APawn> ch= nullptr;
	AMainPlayerController* MyPC = Cast<AMainPlayerController>(NewPlayer);
	if (PlayerCount ==1)
	{
	   SpawnLocation = FVector(110,690, 95);
	   SpawnRotation = FRotator(0, -90, 0);
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
	{
		po->bUseControllerRotationYaw = false;
		if (PlayerCount != 1)
		{
			AMyCharacter* mych = Cast<AMyCharacter>(po);
			mych->SetColision("Monster");
		}
		NewPlayer->Possess(po);
	}
}

UClass* APvPMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (AMyPlayerState* ps = InController->GetPlayerState<AMyPlayerState>())
	{
		switch (ps->MyCharacter_C)
		{
		case Characters::Guiden:
			return  StaticLoadClass(
				AMyCharacter::StaticClass(), nullptr,
				TEXT("/Script/Engine.Blueprint'/Game/bluePrint/PlayGudion.PlayGudion_C'"));
			break;
		case Characters::Warrior:
			return StaticLoadClass(
				AMyCharacter::StaticClass(), nullptr,
				TEXT("/Script/Engine.Blueprint'/Game/bluePrint/PlayWarrior.PlayWarrior_C'"));
			break;
		case Characters::DarkMagion:
			return  StaticLoadClass(
				AMyCharacter::StaticClass(), nullptr,
				TEXT("/Script/Engine.Blueprint'/Game/bluePrint/PlayDark.PlayDark_C'"));
			break;
		}
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}


