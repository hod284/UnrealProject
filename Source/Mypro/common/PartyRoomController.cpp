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
	APawn* mych = Cast<APawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Mychar = Cast<AMyCharacter>(mych);
	if (ui && GetWorld()->GetFirstPlayerController()->IsLocalController())
	{
		ui->AddToViewport();
		ui->SkillInite();
	}
	if (!HasAuthority())
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateLambda([this]() {
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
		GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetGameState(NowGameState::Party);
	}
}

// Called every frame
void APartyRoomController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasAuthority())
	{
		ClientPawn = Cast<AMyCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 1));
		AMyPlayerState* PS = GetWorld()->GetFirstPlayerController()->GetPlayerState<AMyPlayerState>();
		if (PS)
		{
			ui->SetPlayerHpBar(PS->PlayerHP_H);
			ui->SetPlayerMpBar(PS->PlayerMP_H);
			ui->SetotherHpBar(PS->PlayerHP_C);
			ui->SetotherMpBar(PS->PlayerMP_C);
			Mychar->CurrentVelocity_H = PS->CurrentVelocity_H;
			Mychar->CurrentVelocity_C = PS->CurrentVelocity_C;
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
			APawn* mych = PC->GetPawn();
			if (mych)
				mych->SetActorRotation(FRotator(0, 90, 0));
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
			if (PC->PlayerHP_H <= KINDA_SMALL_NUMBER || PC->PlayerHP_C <= KINDA_SMALL_NUMBER)
				UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Virtual_Studio_Kit/Maps/StudioC"));
			Mychar->CurrentVelocity_C = PC->CurrentVelocity_C;
			Mychar->CurrentVelocity_H = PC->CurrentVelocity_H;
			if (HostPawn)
			{
				HostPawn->GetMesh()->SetRelativeRotation(FRotator(0, PC->MeshPitch_h, 0));
				Mychar->SetCameraTarget(HostPawn);
			}
		}
	}

}

