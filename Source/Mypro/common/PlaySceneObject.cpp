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
	Monster = Cast<AMonster>(UGameplayStatics::GetActorOfClass(GetWorld(), AMonster::StaticClass()));
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMonster::StaticClass(), FoundActors_M);
	if(IsValid(CutsceneSequence))
		PlaySequence();
	Po = Cast<APortalClass>(Portal);
	if(Po)
		Po->SetNoColision();
	Portal->SetActorHiddenInGame(true);
}

// Called every frame
void APlaySceneObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Monster->GetDeath())
	{
		if (Po)
			Po->SetColision();
		Portal->SetActorHiddenInGame(false);
	}
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
		ui->SkillInite();
	}
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
	Monster->Start();
}
