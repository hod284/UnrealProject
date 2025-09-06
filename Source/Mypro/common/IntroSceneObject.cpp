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
	GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget()->AddToViewport();
	if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
	{
		Settings->SetScreenResolution(FIntPoint(1920, 1080));
		Settings->ApplySettings(true); 
	}
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
	for (const TPair<Characters, ASelectCharacter*>& pair : SelectCharacterList)
		pair.Value->Inite();
	auto character = SelectCharacterList[choice];
	character->Selected();
}

void AIntroSceneObject::CallthePlayCharacter(Characters choice)
{

	for (const TPair<Characters, ASelectCharacter*>& pair : SelectCharacterList)
		pair.Value->Inite();
	auto character = SelectCharacterList[choice];
	character->StartGame();
	GetWorldTimerManager().ClearTimer(Timerahbdle);
	GetWorld()->GetTimerManager().SetTimer(Timerahbdle, this, &AIntroSceneObject::PlayloadingVideo, 2.0, false);
	ui ->VisuallyStart(ESlateVisibility::Collapsed);
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
	if (GetWorld()->GetAuthGameMode())
	{
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


