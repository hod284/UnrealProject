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
	APawn* mych = Cast<APawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Mychar = Cast<AMyCharacter>(mych);
	if (ui&& GetWorld()->GetFirstPlayerController()->IsLocalController())
	{
		ui->AddToViewport();
		ui->SkillInite();
	}
	if (!HasAuthority())
	{
		GetWorld() ->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateLambda([this]() {
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
			}));
		GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetGameState(NowGameState::pvp);
	}
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
				APawn* mych = PC->GetPawn();
				if(mych)
				mych->SetActorRotation(FRotator(0, 90, 0));
				PC->Sever_GettheMPandHP();
				PC->Sever_GettheMeshPitch();
				PC->Sever_GettheSelectCharacter();
				ui->SetHostImagebyCharacter(PC->MyCharacter_H);
				ui->SetClientImagebyCharacter(PC->MyCharacter_C);
				ui->SetHostHpBar(PC->PlayerHP_H);
				ui->SetHostMpBar(PC->PlayerMP_H);
				ui->SetClientHpBar(PC->PlayerHP_C);
				ui->SetClientMpBar(PC->PlayerMP_C);
				if (HostPawn)
				{
					HostPawn->GetMesh()->SetRelativeRotation(FRotator(0, PC->MeshPitch_h, 0));
					Mychar->SetCameraTarget(HostPawn);
				}
			}
		}
}

