// Fill out your copyright notice in the Description page of Project Settings.


#include "PVPController.h"

// Sets default values
APVPController::APVPController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APVPController::BeginPlay()
{
	Super::BeginPlay();
	UPlayMainUI* ui = Cast<UPlayMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetPlayMainUI_widget());
	if (ui)
	{
		ui->AddToViewport();
		ui->SkillInite();
	}
}

// Called every frame
void APVPController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

