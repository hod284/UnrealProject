// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaySceneObject.h"
#include "../player/MyCharacter.h"
// Sets default values
APlaySceneObject::APlaySceneObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlaySceneObject::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMonster::StaticClass(), FoundActors_M);
	if(IsValid(CutsceneSequence))
		PlaySequence();
}

// Called every frame
void APlaySceneObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void APlaySceneObject::PlaySequence()
{
	AMainPlayerController* PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	AMyCharacter* pawn =Cast<AMyCharacter>(PC->GetPawn());
	pawn->SetBackMoving(true);
	AMainPlayerController* PlayerController = Cast<AMainPlayerController> (UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerController->SetViewTargetWithBlend(CineCamera, 0.f);
	if (CutsceneSequence)
	{
		FMovieSceneSequencePlaybackSettings PlaybackSettings;
		PlaybackSettings.bAutoPlay = true;
		PlaybackSettings.LoopCount.Value = 0;
		SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
			GetWorld(), CutsceneSequence, PlaybackSettings, SequenceActor);
		SequencePlayer->OnFinished.AddDynamic(this, &APlaySceneObject::OnSequenceFinished);
		if (SequencePlayer)
		{
			SequencePlayer->Play();
		}

	}
} 
void APlaySceneObject::OnSequenceFinished()
{
	UPlayMainUI* ui = Cast<UPlayMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetPlayMainUI_widget());
	if (ui)
	{
		ui->AddToViewport();
		switch (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSelectedcharacter())
		{
		case Characters::DarkMagion:
			ui->SetSkill1Inite(TEXT("/Game/image/m1.m1"));
			ui->SetSkill2Inite(TEXT("/Game/image/m2.m2"));
			ui->SetSkill3Inite(TEXT("/Game/image/m3.m3"));
			ui->SetSkill4Inite(TEXT("/Game/image/m4.m4"));
			ui->SetPlayerImage(TEXT("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/giden.giden"));
			break;
		case Characters::Guiden:
			ui->SetSkill1Inite(TEXT("/Game/image/1.1"));
			ui->SetSkill2Inite(TEXT("/Game/image/2.2"));
			ui->SetSkill3Inite(TEXT("/Game/image/3.3"));
			ui->SetSkill4Inite(TEXT("/Game/image/4.4"));
			ui->SetPlayerImage(TEXT("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/greyston.greyston"));
			break;
		case Characters::Warrior:
			ui->SetSkill1Inite(TEXT("/Game/image/1.1"));
			ui->SetSkill2Inite(TEXT("/Game/image/2.2"));
			ui->SetSkill3Inite(TEXT("/Game/image/3.3"));
			ui->SetSkill4Inite(TEXT("/Game/image/4.4"));
			ui->SetPlayerImage(TEXT("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/Auraura.Auraura"));
			break;
		default:
			break;
		}
	}
	AMonster* monster = Cast<AMonster>(UGameplayStatics::GetActorOfClass(GetWorld(), AMonster::StaticClass()));
	AMainPlayerController* PC = Cast<AMainPlayerController>( UGameplayStatics::GetPlayerController(this, 0));
	if (PC)
	{
		if (APawn* Pawn = PC->GetPawn())
		{
			PC->SetViewTargetWithBlend(Pawn, 0.25f);
			AMyCharacter* pawn = Cast<AMyCharacter>(PC->GetPawn());
			pawn->SetBackMoving(false);
		}
	}
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetCusorVisual(UIORNOT::UINot);
	if (AMyPlayerState* PS = Cast<AMyPlayerState>( PC->PlayerState))
	{
		if (ui->GetInventory())
			ui->GetInventory()->SetItemInventory(PS->Inventoryco);
	}
	monster->Start();
}
