// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayerController.h"
#include "MyCharacter.h"
AMainPlayerController::AMainPlayerController()
{
	// tick�� Ȱ��ȭ �ϱ����� ��
	// ���� tick�� ��Ȱ��ȭ �ϰ� ������ �ּ�ó���� �ϸ� �ȴ�.
	PrimaryActorTick.bCanEverTick = true;

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
	// ���콺 Ŀ�� ���̱�
	bShowMouseCursor = GetWorld()->GetGameInstance() ->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Intro ? true : false;
	// Ŭ���̾�Ʈ Ȯ��
	if (IsLocalController())
	{
		if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Intro)
		{
			// ���� �������� ��� ���͵��� ��� ���� ����
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), SceneActorList);
			// Intro UI�� �����ϰ� ����Ʈ�� �߰�
			 GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget()->AddToViewport();
			 if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
			 {
				 Settings->SetScreenResolution(FIntPoint(1920, 1080));
				 Settings->ApplySettings(true); // ��� ����
			 }
		}
		else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
		{
			// Intro UI�� �����ϰ� ����Ʈ�� �߰�
			GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetPlayMainUI_widget() ->AddToViewport();
		}
	}
}


