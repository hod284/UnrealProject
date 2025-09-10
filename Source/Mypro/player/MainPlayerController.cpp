// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayerController.h"
#include "MyCharacter.h"
#include "MyPlayerState.h"
AMainPlayerController::AMainPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;
}

void AMainPlayerController::Tick(float DeltaTime)
{
	bShowMouseCursor = GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetCusorVisual() == UIORNOT::UI ? true : false;
}

void AMainPlayerController::Sever_GettheRotate_Implementation()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
	Client_GettheRotate(PS->Pitch_H, PS->Pitch_C);
}

TSubclassOf<APawn> AMainPlayerController::GetSelectCharactertClass()
{
	TSubclassOf<APawn> LoadedClass = NULL;
	switch (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSelectedcharacter())
	{
	 case Characters::Guiden:
		LoadedClass = StaticLoadClass(
			AMyCharacter::StaticClass(), nullptr,
			TEXT("/Script/Engine.Blueprint'/Game/bluePrint/PlayGudion.PlayGudion_C'")); 
		break;
	case Characters::Warrior:
		LoadedClass = StaticLoadClass(
			AMyCharacter::StaticClass(), nullptr,
			TEXT("/Script/Engine.Blueprint'/Game/bluePrint/PlayWarrior.PlayWarrior_C'")); 
		break;
	case Characters::DarkMagion:
	      LoadedClass = StaticLoadClass(
			  AMyCharacter::StaticClass(), nullptr,
			TEXT("/Script/Engine.Blueprint'/Game/bluePrint/PlayDark.PlayDark_C'")); 
		break;
	}
	return LoadedClass;
}


void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState()== NowGameState::pvp && !HasAuthority())
	{
		Server_SetSelectedPawn();
	}
	SetReplicates(true);
}
void AMainPlayerController::Client_GettheRotate_Implementation(float Pi_h, float Pi_c)
{
	Pitch_c = Pi_c;
	Pitch_h = Pi_h;
}
void AMainPlayerController::SendtheRotate(float Pi_h)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
	PS->Pitch_H =  Pi_h;
}

void AMainPlayerController::Server_SetSelectedPawn_Implementation()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
	PS->MyCharacter = GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSelectedcharacter();
	PS ->SelectCharacter = GetSelectCharactertClass();
}
void  AMainPlayerController::Sever_SendtheRotate_Implementation(float Pi_h)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
	PS->Pitch_C = Pi_h;
}