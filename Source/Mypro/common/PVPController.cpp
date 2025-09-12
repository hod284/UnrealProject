// Fill out your copyright notice in the Description page of Project Settings.


#include "PVPController.h"
#include "../player/MyCharacter.h"
#include "../player/MyPlayerState.h"
#include "../player/MainPlayerController.h"
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
	ui = Cast<UPvPUIClass>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetPvP_widget());
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
		if (HasAuthority())
		{
			AMyPlayerState* PS = GetWorld()->GetFirstPlayerController()->GetPlayerState<AMyPlayerState>();
			ui->SetHostImagebyCharacter(PS->MyCharacter_H);
			ui->SetClientImagebyCharacter(PS->MyCharacter_C);
			ui->SetHostHpBar(PS->PlayerHP_H);
			ui->SetHostMpBar(PS->PlayerMP_H);
			ui->SetClientHpBar(PS->PlayerHP_C);
			ui->SetClientMpBar(PS->PlayerMP_C);
		}
		else
		{
			AMainPlayerController* PC = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
			PC->Sever_GettheSelectCharacter();
			PC->Sever_GettheMPandHP();
			ui->SetHostImagebyCharacter(PC->MyCharacter_H);
			ui->SetClientImagebyCharacter(PC->MyCharacter_C);
			ui->SetHostHpBar(PC->PlayerHP_H);
			ui->SetHostMpBar(PC->PlayerMP_H);
			ui->SetClientHpBar(PC->PlayerHP_C);
			ui->SetClientMpBar(PC->PlayerMP_C);
		}
}

