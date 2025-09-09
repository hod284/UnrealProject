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
	ui->SetMeDiasound(SoundComp);
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
	GetWorldTimerManager().ClearTimer(Timerhandle);
	GetWorld()->GetTimerManager().SetTimer(Timerhandle, this, &AIntroSceneObject::PlayloadingVideo, 2.0, false);
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
	GetWorldTimerManager().ClearTimer(Timerhandle);
	GetWorld()->GetTimerManager().SetTimer(Timerhandle, this, &AIntroSceneObject::PlaySceneLoadAsync, 2.0, false);
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
	FSoftObjectPath LevelPath;
	if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSingorMulti() == SingleORmulti::single)
		LevelPath = FSoftObjectPath(TEXT("/Game/Virtual_Studio_Kit/Maps/Studio_D.Studio_D"));
	else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSingorMulti() == SingleORmulti::Multi)
		LevelPath = FSoftObjectPath(TEXT("/Game/Virtual_Studio_Kit/Maps/StudioB.StudioB"));
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
		GetWorldTimerManager().ClearTimer(Timerhandle);
		GetWorld()->GetTimerManager().SetTimer(Timerhandle, this, &AIntroSceneObject::PlaySceneLoadAsync_stream, 0.5, false);
	}
}

void AIntroSceneObject::FinishedSession(bool ok)
{
	Session->OnFindSessionsCompleteDelegates.RemoveAll(this);
	//LocalId�� ������ �˻��� ��û�ߴ°����� ��Ÿ���� ����/�÷��̾� �ĺ���
	auto localid = GEngine->GetFirstGamePlayer(GetWorld())->GetPreferredUniqueNetId();
	if (ok && Search.IsValid() && Search->SearchResults.Num() > 0)
	{
		// ����������
		Session->OnJoinSessionCompleteDelegates.AddUObject(this, &AIntroSceneObject::JoinSessionComplete);
		Session->JoinSession(*localid, NAME_GameSession, Search->SearchResults[0]);
		return;
	}
	// ������ ȣ��Ʈ�� ����
	FOnlineSessionSettings s;
	s.bIsLANMatch = Search->bIsLanQuery;//LAN ��ġ ����
	s.bShouldAdvertise = true;//������ �ٸ� �÷��̾���� �Ƽ� �ֵ����ϴ°�
	s.NumPublicConnections = 2;// ������
	s.bAllowJoinInProgress = false; // ���������� ����
	Session->OnCreateSessionCompleteDelegates.AddUObject(this, &AIntroSceneObject::CreateSessionComplete);
	Session->DestroySession(NAME_GameSession);
	Session->CreateSession(*localid, NAME_GameSession, s);
}

void AIntroSceneObject::CreateSessionComplete(FName, bool ok)
{
	Session->OnCreateSessionCompleteDelegates.RemoveAll(this);
	if (!ok)
		return;
	  GetWorld()->ServerTravel("/Game/Maps/StudioB?listen");
}
void AIntroSceneObject::JoinSessionComplete(FName, EOnJoinSessionCompleteResult::Type res)
{
	Session->OnJoinSessionCompleteDelegates.RemoveAll(this);
	if (res != EOnJoinSessionCompleteResult::Success)
		return;
	FString add;
	if (Session->GetResolvedConnectString(NAME_GameSession, add))
	{
		if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			PC->ClientTravel(add, TRAVEL_Absolute);
		}
	}
}
void AIntroSceneObject::PlaySceneLoadAsync_stream()
{
	GetWorldTimerManager().ClearTimer(Timerhandle);
	if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSingorMulti() == SingleORmulti::single)
		UGameplayStatics::OpenLevel(this, FName("Studio_D"));
	else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSingorMulti() == SingleORmulti::Multi)
	{
		if (IOnlineSubsystem* oss = IOnlineSubsystem::Get())
			Session = oss ? oss->GetSessionInterface() : nullptr;
		if (!Session.IsValid())
			return;
		// ����ã��
		Search = MakeShared<FOnlineSessionSearch>();
		Search->bIsLanQuery = true;
		Search->MaxSearchResults = 50;
		//FindSessions�� ������ ����� �񵿱�� �˻��ؼ� SearchResults�� ä�� �ִ� �͡�
		Session->OnFindSessionsCompleteDelegates.AddUObject(this, &AIntroSceneObject::FinishedSession);
		auto localid = GEngine->GetFirstGamePlayer(GetWorld())->GetPreferredUniqueNetId();
		Session->FindSessions(*localid, Search.ToSharedRef());
	}
}