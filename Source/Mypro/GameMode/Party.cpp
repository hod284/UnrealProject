// Fill out your copyright notice in the Description page of Project Settings.


#include "Party.h"

#include "../player/MyCharacter.h"
AParty::AParty()
{
	DefaultPawnClass = NULL;
	PlayerControllerClass = AMainPlayerController::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
	SpectatorClass = ASpectatorPawn::StaticClass();
	bUseSeamlessTravel = true;
}
void AParty::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetGameState(NowGameState::Party);
}

void AParty::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (APawn* Old = NewPlayer->GetPawn())
		Old->Destroy();
	RestartPlayer(NewPlayer);
}
void AParty::RestartPlayer(AController* NewPlayer)
{
	bool bIsHostPC = NewPlayer->IsLocalController();
	FVector SpawnLocation;
	FRotator SpawnRotation;
	FVector Scale = FVector(1, 1, 1);
	TSubclassOf<APawn> ch = nullptr;
	AMainPlayerController* MyPC = Cast<AMainPlayerController>(NewPlayer);
	if (bIsHostPC)
	{
		SpawnLocation = FVector(-640, 520, 85);
		SpawnRotation = FRotator(0, -90, 0);
		if (MyPC)
		ch = MyPC->GetSelectCharactertClass();
	}
	else
	{
		SpawnLocation = FVector(60, 520, 85);
		SpawnRotation = FRotator(0, -90, 0);
		if (MyPC)
		ch = GetDefaultPawnClassForController(NewPlayer);
	}
	FTransform T(SpawnRotation, SpawnLocation, Scale);
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	APawn* po = GetWorld()->SpawnActor<APawn>(ch, T, Params);
	if (po)
	{
		po->bUseControllerRotationYaw = false;
		NewPlayer->Possess(po);
	}
}

UClass* AParty::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (AMyPlayerState* ps = InController->GetPlayerState<AMyPlayerState>())
	{
		switch (ps->MyCharacter_C)
		{
		case Characters::Guiden:
			return  StaticLoadClass(
				AMyCharacter::StaticClass(), nullptr,
				TEXT("Class'/Game/bluePrint/PlayGudion.PlayGudion_C'"));
			break;
		case Characters::Warrior:
			return StaticLoadClass(
				AMyCharacter::StaticClass(), nullptr,
				TEXT("Class'/Game/bluePrint/PlayWarrior.PlayWarrior_C'"));
			break;
		case Characters::DarkMagion:
			return  StaticLoadClass(
				AMyCharacter::StaticClass(), nullptr,
				TEXT("Class'/Game/bluePrint/PlayDark.PlayDark_C'"));
			break;
		}
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
} 
