// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyRoomController.h"

// Sets default values
APartyRoomController::APartyRoomController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APartyRoomController::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetCusorVisual(UIORNOT::UINot);
	ui = Cast<UPartyRoomWidgetClass>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetPartyRoom_widget());
	if (ui)
	{
		ui->AddToViewport();
		ui->SkillInite();
	}
	GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateLambda([this]() {
	if (HasAuthority())
	{
		GetWorld()->GetTimerManager().ClearTimer(Timer);
		GetWorld()->GetTimerManager().SetTimer(Timer, [this]()
			{
				if (Portal && !CanMaxium && ClientPawnSpawn)
				{
					if (AddMaxium < Maxium)
					{
						AddMaxium += 2;
						Portal->Spawn();
					}
					else
						CanMaxium = true;
				}
				if (AddMaxium == 0)
				{
					CanMaxium = false;
				}
				if (ClientPawn&& !ClientPawnSpawn)
				{
					ClientPawnSpawn = true;
				}
			}, 6.0f, true,2.0f);
	}
	}));
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetGameState(NowGameState::Party);
}

// Called every frame
void APartyRoomController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasAuthority())
	{
		APawn* mych = Cast<APawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
		Mychar = Cast<AMyCharacter>(mych);
		AMyPlayerState* PS = GetWorld()->GetFirstPlayerController()->GetPlayerState<AMyPlayerState>();
		if (PS)
		{
			ui->SetPlayerImagebyCharacter(PS->MyCharacter_H);
			ui->SetPlayerOtherImagebyCharacter(PS->MyCharacter_C);
			ui->SetPlayerHpBar(PS->PlayerHP_H);
			ui->SetPlayerMpBar(PS->PlayerMP_H);
			ui->SetotherHpBar(PS->PlayerHP_C);
			ui->SetotherMpBar(PS->PlayerMP_C);
			if (Mychar)
			{
				if (ClientPawn == NULL)
				ClientPawn = Cast<AMyCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 1));
				Mychar->CurrentVelocity_H = PS->CurrentVelocity_H;
				Mychar->CurrentVelocity_C = PS->CurrentVelocity_C;
			}
			if (PS->PlayerHP_H <= KINDA_SMALL_NUMBER|| Portal->GetGototheMain())
			{
				GetWorld()->GetTimerManager().ClearTimer(Timer);
			    UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Virtual_Studio_Kit/Maps/StudioC"));
			}
			if (ClientPawn&& PS->PlayerHP_C > KINDA_SMALL_NUMBER)
			{
				ClientPawn->GetMesh()->SetRelativeRotation(FRotator(0, PS->MeshPitch_C, 0));
			}
		}
	}
	else
	{
		AMainPlayerController* PC = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
		if (PC)
		{
			APawn* mych = Cast<APawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
			Mychar = Cast<AMyCharacter>(mych);
			if (Mychar)
			{
				Mychar->SetActorRotation(FRotator(0, -90, 0));
				Mychar->CurrentVelocity_C = PC->CurrentVelocity_C;
				Mychar->CurrentVelocity_H = PC->CurrentVelocity_H;
				if (HostPawn == NULL)
				{
					for (TActorIterator<AMyCharacter> It(GetWorld()); It; ++It)
					{
						if (Mychar != *It)
							HostPawn = *It;
					}
				}
			}
			PC->Sever_GettheMPandHP();
			PC->Sever_GettheMeshPitch();
			PC->Sever_GettheSelectCharacter();
			PC->Server_GetttheVelocity();
			ui->SetPlayerOtherImagebyCharacter(PC->MyCharacter_H);
			ui->SetPlayerImagebyCharacter(PC->MyCharacter_C);
			ui->SetotherHpBar(PC->PlayerHP_H);
			ui->SetotherMpBar(PC->PlayerMP_H);
			ui->SetPlayerHpBar(PC->PlayerHP_C);
			ui->SetPlayerMpBar(PC->PlayerMP_C);
			if (PC->PlayerHP_C <= KINDA_SMALL_NUMBER&& PC->PlayerHP_H > KINDA_SMALL_NUMBER)
			{
				if (HostPawn&& PC->GetViewTarget() != HostPawn)
					PC->SetViewTarget(HostPawn);
				if(Mychar)
				PC->Server_DClient(Mychar);
			}
			if (HostPawn && PC->PlayerHP_H > KINDA_SMALL_NUMBER)
			{
				HostPawn->GetMesh()->SetRelativeRotation(FRotator(0, PC->MeshPitch_h, 0));
			}
			if (Portal&&Portal->GetGototheMain())
			{
				GetWorld()->GetTimerManager().ClearTimer(Timer);
				PC->Server_EndPvP();
			}
		}
	}
}

