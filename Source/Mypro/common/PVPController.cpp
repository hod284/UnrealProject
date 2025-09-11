// Fill out your copyright notice in the Description page of Project Settings.


#include "PVPController.h"
#include "../player/MyCharacter.h"
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
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetCusorVisual(UIORNOT::UINot);
	UPlayMainUI* ui = Cast<UPlayMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetPlayMainUI_widget());
	if (ui)
	{
		ui->AddToViewport();
		ui->SkillInite();
	}
	if (!HasAuthority())
	{
		APawn* mych = Cast<APawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
		AMyCharacter* mychar = Cast<AMyCharacter>(mych);
		mychar->SetColision("Monster");
	}
}

// Called every frame
void APVPController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!HasAuthority())
	{
		APawn* mych1 = Cast<APawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
		mych1->SetActorRotation(FRotator(0, 90, 0));
	}
}

