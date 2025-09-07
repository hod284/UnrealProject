// Fill out your copyright notice in the Description page of Project Settings.


#include "WinLevelController.h"

// Sets default values
AWinLevelController::AWinLevelController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWinLevelController::BeginPlay()
{
	Super::BeginPlay();
	switch (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSelectedcharacter())
	{
	case  Characters::Warrior:
		PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		PlayerController->SetViewTargetWithBlend(Auroa, cameratime);
		Giden->Destroy();
		GraySton->Destroy();
		break;
	case  Characters::DarkMagion:
		 PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		PlayerController->SetViewTargetWithBlend(Giden, cameratime);
		Auroa->Destroy();
		GraySton->Destroy();
		break;
	case  Characters::Guiden:
		 PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		PlayerController->SetViewTargetWithBlend(GraySton, cameratime);
		Auroa->Destroy();
		Giden->Destroy();
		break;
	} 
	GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetWiner_widget()->AddToViewport();
}

// Called every frame
void AWinLevelController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

