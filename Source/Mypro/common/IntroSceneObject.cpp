// Fill out your copyright notice in the Description page of Project Settings.


#include "IntroSceneObject.h"

// Sets default values
AIntroSceneObject::AIntroSceneObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AIntroSceneObject::BeginPlay()
{
	Super::BeginPlay();
    SoundComp = NewObject<UMediaSoundComponent>(this);
	SoundComp->SetMediaPlayer(MyMediaPlayer_intro);
	SoundComp->RegisterComponent();
}

// Called every frame
void AIntroSceneObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIntroSceneObject::CalltheSelectCharacter(Characters choice)
{
	// 티멥에 있는 캐릭터 클래스를 for문을 통해 전부초기화
	for (const TPair<Characters, ASelectCharacter*>& pair : SelectCharacterList)
		pair.Value->Inite();
	auto character = SelectCharacterList[choice];
	character->Selected();
}

void AIntroSceneObject::CallthePlayCharacter(Characters choice)
{
	// 티멥에 있는 캐릭터 클래스를 for문을 통해 전부초기화
	for (const TPair<Characters, ASelectCharacter*>& pair : SelectCharacterList)
		pair.Value->Inite();
	auto character = SelectCharacterList[choice];
	character->StartGame();
	GetWorldTimerManager().ClearTimer(Timerahbdle);
	GetWorld()->GetTimerManager().SetTimer(Timerahbdle, this, &AIntroSceneObject::PlayloadingVideo, 2.0, false);
}

void AIntroSceneObject::PlaySequence()
{  
	if (CutsceneSequence)
	{
		FMovieSceneSequencePlaybackSettings PlaybackSettings;
		PlaybackSettings.bAutoPlay = true;
		PlaybackSettings.LoopCount.Value=0;
		SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
			GetWorld(), CutsceneSequence, PlaybackSettings, SequenceActor);
		 
		if (SequencePlayer)
		{
			SequencePlayer->Play();
		}
	}
}
void AIntroSceneObject::PlayloadingVideo()
{
	UIntroMainUI* ui = Cast<UIntroMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget());
	if (ui)
	{
		MyMediaPlayer_loading->Play();
		ui->SetSwitcherIndex(2);
		SoundComp->SetMediaPlayer(MyMediaPlayer_loading);
		SoundComp->RegisterComponent();
	}
	GetWorldTimerManager().ClearTimer(Timerahbdle);
	GetWorld()->GetTimerManager().SetTimer(Timerahbdle, this, &AIntroSceneObject::PlaySceneLoadAsync, 2.0, false);
}
void AIntroSceneObject::PlaySceneLoad(const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result)
{
	if (Result == EAsyncLoadingResult::Succeeded)
	{
		GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetGameState(NowGameState::playgame);
		UGameplayStatics::OpenLevel(GetWorld(), PackageName);
	}
	else
	UE_LOG(LogMypro, Warning, TEXT("SceneLoadFail"))

}

void AIntroSceneObject::PlaySceneLoadAsync()
{
	FSoftObjectPath LevelPath(TEXT("/Game/Virtual_Studio_Kit/Maps/Studio_D.Studio_D'"));
	if (LevelPath.IsValid())
	{
		LoadPackageAsync(LevelPath.ToString(), FLoadPackageAsyncDelegate::CreateUObject(this, &AIntroSceneObject::PlaySceneLoad), 0, PKG_ContainsMap);
	}
}


