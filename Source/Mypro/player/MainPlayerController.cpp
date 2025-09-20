// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayerController.h"
#include "MyCharacter.h"
#include "MyPlayerState.h"
AMainPlayerController::AMainPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;
}

TSubclassOf<APawn> AMainPlayerController::GetSelectCharactertClass()
{
	TSubclassOf<APawn> LoadedClass = NULL;
	switch (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSelectedcharacter())
	{
	 case Characters::Guiden:
		LoadedClass = StaticLoadClass(
			AMyCharacter::StaticClass(), nullptr,
			TEXT("/Script/Engine.Blueprint'/Game/bluePrint/PlayGudion.PlayGudion_C'")); 
		break;
	case Characters::Warrior:
		LoadedClass = StaticLoadClass(
			AMyCharacter::StaticClass(), nullptr,
			TEXT("/Script/Engine.Blueprint'/Game/bluePrint/PlayWarrior.PlayWarrior_C'")); 
		break;
	case Characters::DarkMagion:
	      LoadedClass = StaticLoadClass(
			  AMyCharacter::StaticClass(), nullptr,
			TEXT("/Script/Engine.Blueprint'/Game/bluePrint/PlayDark.PlayDark_C'")); 
		break;
	}
	return LoadedClass;
}
void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateLambda ([this]() {
		UPvPUIClass* ui = Cast<UPvPUIClass>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetPvP_widget());
		if (ui)
		{
			if (HasAuthority())
			{
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
		}
	}));
	SetReplicates(true);
}
void AMainPlayerController::Tick(float DeltaTime)
{
	bShowMouseCursor = GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetCusorVisual() == UIORNOT::UI ? true : false;
}
void AMainPlayerController::Sever_GettheRotate_Implementation()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
	Client_GettheRotate(PS->Pitch_H, PS->Pitch_C);
}
void AMainPlayerController::Client_GettheRotate_Implementation(float Pi_h, float Pi_c)
{
	Pitch_c = Pi_c;
	Pitch_h = Pi_h;
}
void AMainPlayerController::Sever_SendtheReady_Implementation(bool ready)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
	PS->Ready_C = ready;
}
void AMainPlayerController::Server_SetSelectedPawn_Implementation(Characters CH)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
	PS ->MyCharacter_C = CH;
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetSelectCharacter_client(CH);
}
void  AMainPlayerController::Sever_SendtheRotate_Implementation(float Pi_h)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
	PS->Pitch_C = Pi_h;
}
void AMainPlayerController::Sever_GettheReady_Implementation()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
	Client_GettheReady(PS->Ready_H, PS->Ready_C);
}

void AMainPlayerController::Client_GettheReady_Implementation(bool ready_h, bool ready_c)
{
	Ready_c = ready_c;
	Ready_h = ready_h;
}
void AMainPlayerController::Sever_GettheSelectCharacter_Implementation()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
	Client_GettheSelectCharacter(PS->MyCharacter_C, PS->MyCharacter_H);
}

void AMainPlayerController::Client_GettheSelectCharacter_Implementation(Characters ch_c, Characters ch_h)
{
	MyCharacter_C = ch_c;
	MyCharacter_H = ch_h;
}

void AMainPlayerController::Sever_GettheMPandHP_Implementation()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
	Client_GettheMPandHP(PS->PlayerHP_H, PS->PlayerMP_H, PS->PlayerHP_C, PS->PlayerMP_C);
}

void AMainPlayerController::Client_GettheMPandHP_Implementation(float Hp_H, float Mp_H, float Hp_C, float Mp_C)
{
	PlayerHP_H = Hp_H;
	PlayerMP_H = Mp_H;
	PlayerHP_C = Hp_C;
	PlayerMP_C = Mp_C;
}
void AMainPlayerController::Sever_SendtheClientHP_Implementation(float damage)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
	PS->PlayerHPtotal_C -= damage;
	float hpb = (PS->PlayerHPtotal_C / PS->PlayerHPtotalconst_C) * 100;
	hpb = hpb / 100.0f;
	PS->PlayerHP_C = hpb;
}

void AMainPlayerController::Sever_SendtheClientMP_Implementation(float Mp)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
	PS->PlayerMP_C = Mp;
}
void AMainPlayerController::Sever_SendtheClientMeshPitch_Implementation(float Pitch)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
	PS->MeshPitch_C = Pitch;
}
void AMainPlayerController::Sever_GettheMeshPitch_Implementation()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
	UE_LOG(LogMypro, Warning, TEXT("host rotate: %f"), PS->MeshPitch_H);
	Client_GedtheMeshRotate(PS->MeshPitch_H ,PS->MeshPitch_C);
}
void AMainPlayerController::Client_GedtheMeshRotate_Implementation(float RO_H, float RO_C)
{
	MeshPitch_h = RO_H;
	UE_LOG(LogMypro, Warning, TEXT("host rotate: %f"), MeshPitch_h);
	MeshPitch_c = RO_C;
}
void AMainPlayerController::Server_SendtheDamage_Implementation(AActor* actor, float damage)
{
	AMyCharacter* mychar = Cast<AMyCharacter>(actor);
	if (mychar)
	{
		if (!mychar->ClientAttack)
			UGameplayStatics::ApplyDamage(mychar, damage, GetInstigatorController(), this, UDamageType::StaticClass());
		mychar->ClientAttack = true;
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([mychar]() {mychar->ClientAttack = false; }), 0.3f, false);
	}
}
void AMainPlayerController::Server_HittheDamageHost_Implementation(AActor* actor, float damage)
{
	AMyCharacter* mychar = Cast<AMyCharacter>(actor);
	if (mychar)
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC)
		{
			AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
			PS->PlayerHPtotal_H -= damage;
		   float hpb = (PS->PlayerHPtotal_H / PS->PlayerHPtotalconst_H) * 100;
		   hpb = hpb / 100.0f;
		   PS->PlayerHP_H = hpb;
		}
	}
}

void AMainPlayerController::Server_HittheDamageClient_Implementation(AActor* actor, float damage)
{
		AMyCharacter* mychar = Cast<AMyCharacter>(actor);
		if (mychar)
		{
			APlayerController* PC = GetWorld()->GetFirstPlayerController();
			if (PC )
			{
				AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
				PS->PlayerHPtotal_C -= damage;
				float hpb = (PS->PlayerHPtotal_C / PS->PlayerHPtotalconst_C) * 100;
				hpb = hpb / 100.0f;
				PS->PlayerHP_C = hpb;
			}
		}
}

void AMainPlayerController::Server_SendthetotalHP_Implementation(float hp)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
	PS->PlayerHPtotal_C = hp;
	PS->PlayerHPtotalconst_C = hp;
}
void AMainPlayerController::Server_SendtheVelocity_Implementation(FVector ve)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
	PS->CurrentVelocity_C = ve;
}

void AMainPlayerController::Server_GetttheVelocity_Implementation()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
	Client_GetttheVelocity(PS->CurrentVelocity_H, PS->CurrentVelocity_C);
}

void AMainPlayerController::Client_GetttheVelocity_Implementation(FVector ve_h, FVector ve_c)
{
	CurrentVelocity_H = ve_h;
	CurrentVelocity_C = ve_c;
}