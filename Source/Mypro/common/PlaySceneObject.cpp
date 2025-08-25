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
	GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetPlayMainUI_widget()->AddToViewport();
	AMonster* monster = Cast<AMonster>(UGameplayStatics::GetActorOfClass(GetWorld(), AMonster::StaticClass()));
	AMainPlayerController* PC = Cast<AMainPlayerController>( UGameplayStatics::GetPlayerController(this, 0));
	if (PC)
	{
		// ¿ø·¡ ÇÃ·¹ÀÌ¾î ºä·Î º¹±Í
		if (APawn* Pawn = PC->GetPawn())
		{
			PC->SetViewTargetWithBlend(Pawn, 0.25f);
			AMyCharacter* pawn = Cast<AMyCharacter>(PC->GetPawn());
			pawn->SetBackMoving(false);
		}
	}
	monster->Start();
}
