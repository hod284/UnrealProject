// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayerController.h"
#include "MyCharacter.h"
AMainPlayerController::AMainPlayerController()
{
	// tick�� Ȱ��ȭ �ϱ����� ��
	// ���� tick�� ��Ȱ��ȭ �ϰ� ������ �ּ�ó���� �ϸ� �ȴ�.
	PrimaryActorTick.bCanEverTick = true;
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;
}

void AMainPlayerController::Tick(float DeltaTime)
{
	bShowMouseCursor = GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetCusorVisual() == UIORNOT::UI ? true : false;
}

TSubclassOf<APawn> AMainPlayerController::GetSelectCharactertClass()
{
	// ��ȯ��� ������ ���� �ε�Ŭ���� ����� �ʱ�ȭ
	TSubclassOf<APawn> LoadedClass = NULL;
	switch (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSelectedcharacter())
	{
	 case Characters::Guiden:
		LoadedClass = StaticLoadClass(
			AMyCharacter::StaticClass(), nullptr,
			TEXT("/Script/Engine.Blueprint'/Game/bluePrint/PlayGudion.PlayGudion_C'")); // _C ��!
		break;
	case Characters::Warrior:
		LoadedClass = StaticLoadClass(
			AMyCharacter::StaticClass(), nullptr,
			TEXT("/Script/Engine.Blueprint'/Game/bluePrint/PlayWarrior.PlayWarrior_C'")); // _C ��!
		break;
	case Characters::DarkMagion:
	      LoadedClass = StaticLoadClass(
			  AMyCharacter::StaticClass(), nullptr,
			TEXT("/Script/Engine.Blueprint'/Game/bluePrint/PlayDark.PlayDark_C'")); // _C ��!
		break;
	}
	return LoadedClass;
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// Ŭ���̾�Ʈ Ȯ��
	if (IsLocalController())
	{
		if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Intro)
		{
			GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetCusorVisual(UIORNOT::UI);
			// ���� �������� ��� ���͵��� ��� ���� ����
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), SceneActorList);
		}
		else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
		{
			GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetPlayMainUI_widget()->AddToViewport();
		}
	}
}


