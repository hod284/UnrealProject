// Fill out your copyright notice in the Description page of Project Settings.


#include "PVPController.h"
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
	if (ui&& GetWorld()->GetFirstPlayerController()->IsLocalController())
	{
		ui->AddToViewport();
		ui->SkillInite();
	}
	GetWorld() ->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateLambda([this]() {
	if (HasAuthority())
	{

		APawn* mych = Cast<APawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
		Mychar = Cast<AMyCharacter>(mych);
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC)
		{
			AMyPlayerState* PS = PC->GetPlayerState<AMyPlayerState>();
			if (PS)
			{
				ui->SetHostImagebyCharacter(PS->MyCharacter_H);
				ui->SetClientImagebyCharacter(PS->MyCharacter_C);
			}
		}
	}
	else
	{
		APawn* mych = Cast<APawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
		Mychar = Cast<AMyCharacter>(mych);
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCharacter::StaticClass(), Players);
		for (AActor* actor : Players)
		{
			AMyCharacter* otherchar = Cast<AMyCharacter>(actor);
			if (otherchar != Mychar)
			{
				HostPawn = otherchar;
				break;
			}
			UE_LOG(LogTemp, Warning, TEXT("Players:%s"), *actor->GetName());
		}
	}
	}));
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetGameState(NowGameState::pvp);
	
}

// Called every frame
void APVPController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		if (HasAuthority())
		{
			ClientPawn = Cast<AMyCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 1));
			AMyPlayerState* PS = GetWorld()->GetFirstPlayerController()->GetPlayerState<AMyPlayerState>();
			if (PS)
			{
				ui->SetHostHpBar(PS->PlayerHP_H);
				ui->SetHostMpBar(PS->PlayerMP_H);
				ui->SetClientHpBar(PS->PlayerHP_C);
				ui->SetClientMpBar(PS->PlayerMP_C);
				if (Mychar)
				{
					Mychar->CurrentVelocity_H = PS->CurrentVelocity_H;
					Mychar->CurrentVelocity_C = PS->CurrentVelocity_C;
				}
				if (PS->PlayerHP_H <= KINDA_SMALL_NUMBER || PS->PlayerHP_C <= KINDA_SMALL_NUMBER)
					UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Virtual_Studio_Kit/Maps/StudioC"));
			}
			if (ClientPawn)
			{
				Mychar->SetCameraTarget(ClientPawn);
				ClientPawn->GetMesh()->SetRelativeRotation(FRotator(0, PS->MeshPitch_C, 0));
			}
		}
		else
		{
			
			AMainPlayerController* PC = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
			if (PC)
			{
				if (Mychar)
				{
					Mychar->SetActorRotation(FRotator(0, 90, 0));
					Mychar->CurrentVelocity_C = PC->CurrentVelocity_C;
					Mychar->CurrentVelocity_H = PC->CurrentVelocity_H;
				}
				PC->Sever_GettheMPandHP();
				PC->Sever_GettheMeshPitch();
				PC->Sever_GettheSelectCharacter();
				PC->Server_GetttheVelocity();
				ui->SetHostImagebyCharacter(PC->MyCharacter_H);
				ui->SetClientImagebyCharacter(PC->MyCharacter_C);
				ui->SetHostHpBar(PC->PlayerHP_H);
				ui->SetHostMpBar(PC->PlayerMP_H);
				ui->SetClientHpBar(PC->PlayerHP_C);
				ui->SetClientMpBar(PC->PlayerMP_C);
				if (PC->PlayerHP_H <= KINDA_SMALL_NUMBER || PC->PlayerHP_C <= KINDA_SMALL_NUMBER)
					UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Virtual_Studio_Kit/Maps/StudioC"));
				if (HostPawn)
				{
					HostPawn->GetMesh()->SetRelativeRotation(FRotator(0, PC->MeshPitch_h, 0));
					Mychar->SetCameraTarget(HostPawn);
					HostPawn->SetColision("Monster");
				}
			}
		}
}

