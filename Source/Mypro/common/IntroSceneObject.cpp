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
	ui = Cast<UIntroMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget());
	SoundComp = NewObject<UMediaSoundComponent>(this);
	SoundComp->SetMediaPlayer(MyMediaPlayer_intro);
	SoundComp->RegisterComponent();
}

// Called every frame
void AIntroSceneObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ui)
	{
		if (Handle.IsValid() && !Handle->HasLoadCompleted())
			ui->SetPercenttext(Handle->GetProgress());
	}
}

void AIntroSceneObject::CalltheSelectCharacter(Characters choice)
{
	// Ƽ�㿡 �ִ� ĳ���� Ŭ������ for���� ���� �����ʱ�ȭ
	for (const TPair<Characters, ASelectCharacter*>& pair : SelectCharacterList)
		pair.Value->Inite();
	auto character = SelectCharacterList[choice];
	character->Selected();
}

void AIntroSceneObject::CallthePlayCharacter(Characters choice)
{
	// Ƽ�㿡 �ִ� ĳ���� Ŭ������ for���� ���� �����ʱ�ȭ
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
		UGameplayStatics::OpenLevel(GetWorld(), PackageName);
	}
}

void AIntroSceneObject::PlaySceneLoadAsync()
{
	GetWorldTimerManager().ClearTimer(Timerahbdle);
	FSoftObjectPath LevelPath(TEXT("/Game/Virtual_Studio_Kit/Maps/Studio_D.Studio_D'"));
	if (LevelPath.IsValid())
	{
		// �񵿱�� �̸� �ε带 ������ ���� �󸶳� �ε带 �ߴ��� �ۼ�Ʈ�� �� ���� ��� STREAMMAMAGER�� ��ȯ
		//LoadPackageAsync(LevelPath.ToString(), FLoadPackageAsyncDelegate::CreateUObject(this, &AIntroSceneObject::PlaySceneLoad), 0, PKG_ContainsMap);
		auto& SM = UAssetManager::GetStreamableManager();
		Handle = SM.RequestAsyncLoad(LevelPath, FStreamableDelegate::CreateUObject(this,&AIntroSceneObject::LevelLoadComplete));
	}
}
void AIntroSceneObject::LevelLoadComplete()
{
	if(ui)
	ui->SetPercenttext(1.0f);
	Handle->ReleaseHandle();
	Handle.Reset();
	// ȣ��Ʈ���� Ŭ���̾�Ʈ���� �˻�
	if (GetWorld()->GetAuthGameMode())
	{
		//�� ��ȯ �� �÷��̾�� �Ϻ� ���� ���¸� �����ϸ鼭 �ε巴�� �̵��ϴ� ����� �Ѵ� �÷����Դϴ�.
		GetWorld()->GetAuthGameMode()->bUseSeamlessTravel = true;
		GetWorldTimerManager().ClearTimer(Timerahbdle);
		GetWorld()->GetTimerManager().SetTimer(Timerahbdle, this, &AIntroSceneObject::PlaySceneLoadAsync_stream, 0.5, false);
	}
}
void AIntroSceneObject::PlaySceneLoadAsync_stream()
{
	GetWorldTimerManager().ClearTimer(Timerahbdle);
   GetWorld()->ServerTravel("/Game/Virtual_Studio_Kit/Maps/Studio_D?listen'");
}


