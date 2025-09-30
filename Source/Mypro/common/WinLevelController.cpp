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
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetCusorVisual(UIORNOT::UI);
	switch (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSelectedcharacter())
	{
	case  Characters::Warrior:
		PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		PlayerController->SetViewTargetWithBlend(Auroa, cameratime);
		Giden->SetActorHiddenInGame(true);
		GraySton->SetActorHiddenInGame(true);
		break;
	case  Characters::DarkMagion:
		 PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		PlayerController->SetViewTargetWithBlend(Giden, cameratime);
		Auroa->SetActorHiddenInGame(true);
		GraySton->SetActorHiddenInGame(true);
		break;
	case  Characters::Guiden:
		 PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		PlayerController->SetViewTargetWithBlend(GraySton, cameratime);
		Auroa->SetActorHiddenInGame(true);
		Giden->SetActorHiddenInGame(true);
		break;
	} 
	GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetWiner_widget()->AddToViewport();
	UWinerWidgetClass*ui =Cast<UWinerWidgetClass>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetWiner_widget());
	ui->SetMeDiasound(Audiocompo ->FindComponentByClass<UAudioComponent>());
}

// Called every frame
void AWinLevelController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

