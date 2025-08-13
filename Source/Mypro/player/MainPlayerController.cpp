// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayerController.h"
#include "MyCharacter.h"
AMainPlayerController::AMainPlayerController()
{
	// tick를 활성화 하기위한 줄
	// 만약 tick를 비활성화 하고 싶으면 주석처릴를 하면 된다.
	PrimaryActorTick.bCanEverTick = true;

}

TSubclassOf<APawn> AMainPlayerController::GetSelectCharactertClass()
{
	// 반환경로 보장을 위해 로드클래스 선언및 초기화
	TSubclassOf<APawn> LoadedClass = NULL;
	switch (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSelectedcharacter())
	{
	 case Characters::Guiden:
		LoadedClass = StaticLoadClass(
			AMyCharacter::StaticClass(), nullptr,
			TEXT("/Script/Engine.Blueprint'/Game/bluePrint/PlayGudion.PlayGudion_C'")); // _C 꼭!
		break;
	case Characters::Warrior:
		LoadedClass = StaticLoadClass(
			AMyCharacter::StaticClass(), nullptr,
			TEXT("/Script/Engine.Blueprint'/Game/bluePrint/PlayWarrior.PlayWarrior_C'")); // _C 꼭!
		break;
	case Characters::DarkMagion:
	      LoadedClass = StaticLoadClass(
			  AMyCharacter::StaticClass(), nullptr,
			TEXT("/Script/Engine.Blueprint'/Game/bluePrint/PlayDark.PlayDark_C'")); // _C 꼭!
		break;
	}
	return LoadedClass;
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// 마우스 커서 보이기
	bShowMouseCursor = GetWorld()->GetGameInstance() ->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Intro ? true : false;
	// 클라이언트 확인
	if (IsLocalController())
	{
		if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Intro)
		{
			// 현재 레벨에서 모든 액터들을 들고 오는 로직
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), SceneActorList);
			// Intro UI를 생성하고 뷰포트에 추가
			 GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget()->AddToViewport();
			 if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
			 {
				 Settings->SetScreenResolution(FIntPoint(1920, 1080));
				 Settings->ApplySettings(true); // 즉시 적용
			 }
		}
		else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
		{
			// Intro UI를 생성하고 뷰포트에 추가
			GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetPlayMainUI_widget() ->AddToViewport();
		}
	}
}


