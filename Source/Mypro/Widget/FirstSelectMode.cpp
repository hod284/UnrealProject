// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstSelectMode.h"

void UFirstSelectMode::NativeConstruct()
{
	Super::NativeConstruct();
	// 싱글버튼 호버 이벤트 연결
	if(!SingleButton->OnHovered.IsBound())
	SingleButton->OnHovered.AddDynamic(this, &UFirstSelectMode::HoverSingleButton);
	// 싱글버튼 언호버 이벤트 연결
	if (!SingleButton->OnUnhovered.IsBound())
	SingleButton->OnUnhovered.AddDynamic(this, &UFirstSelectMode::UnHoverSingleButton);
	// 싱글버튼 클릭 이벤트 연결
	if (!SingleButton->OnClicked.IsBound())
	SingleButton->OnClicked.AddDynamic(this, &UFirstSelectMode::ClickSingleButton);
	// 멀티버튼 호버 이벤트 연결
	if (!MultiButton->OnHovered.IsBound())
	MultiButton->OnHovered.AddDynamic(this, &UFirstSelectMode::HoverMultiButton);
	// 멀티버튼 언호버 이벤트 연결
	if (!MultiButton->OnUnhovered.IsBound())
	MultiButton->OnUnhovered.AddDynamic(this, &UFirstSelectMode::UnHoverMultiButton);
	// 멀티버튼 클릭 이벤트 연결
	if (!MultiButton->OnClicked.IsBound())
	MultiButton->OnClicked.AddDynamic(this, &UFirstSelectMode::ClickMultiButton);
	// 멀티버튼 호버 이벤트 연결
	if (!multipartybutton->OnHovered.IsBound())
		multipartybutton->OnHovered.AddDynamic(this, &UFirstSelectMode::HoverMultiPartyButton);
	// 멀티버튼 언호버 이벤트 연결
	if (!multipartybutton->OnUnhovered.IsBound())
		multipartybutton->OnUnhovered.AddDynamic(this, &UFirstSelectMode::UnHoverMultiPartyButton);
	// 멀티버튼 클릭 이벤트 연결
	if (!multipartybutton->OnClicked.IsBound())
		multipartybutton->OnClicked.AddDynamic(this, &UFirstSelectMode::ClickMultiPartyButton);
}

void UFirstSelectMode::FirstSelectCharacter()
{
	AIntroSceneObject* IntroSceneObject = Cast<AIntroSceneObject>(UGameplayStatics::GetActorOfClass(GetWorld(), AIntroSceneObject::StaticClass()));
		if (IntroSceneObject)
		{
			if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSelectedcharacter() == Characters::None)
			{
				GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetSelectCharacter(Characters::Warrior);
				IntroSceneObject->CalltheSelectCharacter(Characters::Warrior);
			}
			else
			{
				IntroSceneObject->CalltheSelectCharacter(GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSelectedcharacter());
			}
		}
	
}

void UFirstSelectMode::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UFirstSelectMode::HoverSingleButton()
{
	// 싱글 버튼 호버 시 애니메이션 재생
	if(single)
		PlayAnimation(single,0.0,0,EUMGSequencePlayMode::Forward,1.0f);
}

void UFirstSelectMode::UnHoverSingleButton()
{
	// 싱글 버튼 언호버 시 애니메이션 정지
	if (single)
		StopAnimation(single);
}

void UFirstSelectMode::HoverMultiButton()
{
	// 멀티 버튼 호버 시 애니메이션 재생
	if(multi)
		PlayAnimation(multi,0.0, 0, EUMGSequencePlayMode::Forward, 1.0f);
}

void UFirstSelectMode::UnHoverMultiButton()
{
	// 멀티 버튼 언호버 시 애니메이션 정지
	if (multi)
		StopAnimation(multi);
}

void UFirstSelectMode::HoverMultiPartyButton()
{
	// 멀티 버튼 호버 시 애니메이션 재생
	if (multiparty)
		PlayAnimation(multiparty, 0.0, 0, EUMGSequencePlayMode::Forward, 1.0f);
}

void UFirstSelectMode::UnHoverMultiPartyButton()
{
	if (multiparty)
		StopAnimation(multiparty);
}

void UFirstSelectMode::ClickSingleButton()
{
	// 싱글 버튼 클릭 시 IntroMainUI의 스위처 인덱스를 1로 설정하여 캐릭터 선택화면 으로 전환
	UIntroMainUI* ui = Cast<UIntroMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget());
	if (ui)
	{
		FirstSelectCharacter();
		ui->SetSwitcherIndex(1);
		GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetSingorMulti(SingleORmulti::single);
	}
}

void UFirstSelectMode::ClickMultiButton()
{
	// 멀티 버튼 클릭 시 IntroMainUI의 스위처 인덱스를 1로 설정하여 캐릭터 선택 화면으로 전환
	UIntroMainUI* ui = Cast<UIntroMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget());
	if (ui)
	{
		GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetSingorMulti(SingleORmulti::Multi);
	}
	if (IOnlineSubsystem* oss = IOnlineSubsystem::Get())
		Session = oss ? oss->GetSessionInterface() : nullptr;
	if (!Session.IsValid())
		return;
	Search = MakeShared<FOnlineSessionSearch>();
	Search->bIsLanQuery = true;
	Search->MaxSearchResults = 50;
	Session->OnFindSessionsCompleteDelegates.AddUObject(this, &UFirstSelectMode::FinishedSession);
	auto localid = GEngine->GetFirstGamePlayer(GetWorld())->GetPreferredUniqueNetId();
	Session->FindSessions(*localid, Search.ToSharedRef());
}

void UFirstSelectMode::ClickMultiPartyButton()
{
	// 멀티 버튼 클릭 시 IntroMainUI의 스위처 인덱스를 1로 설정하여 캐릭터 선택 화면으로 전환
	UIntroMainUI* ui = Cast<UIntroMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget());
	if (ui)
	{
		GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetSingorMulti(SingleORmulti::MultiParty);
	}
	if (IOnlineSubsystem* oss = IOnlineSubsystem::Get())
		Session = oss ? oss->GetSessionInterface() : nullptr;
	if (!Session.IsValid())
		return;
	FindRetries = 0;
	Search = MakeShared<FOnlineSessionSearch>();
	Search->bIsLanQuery = true;
	Search->MaxSearchResults = 50;
	Session->OnFindSessionsCompleteDelegates.AddUObject(this, &UFirstSelectMode::FinishedSession);
	auto localid = GEngine->GetFirstGamePlayer(GetWorld())->GetPreferredUniqueNetId();
	Session->FindSessions(*localid, Search.ToSharedRef());
}

void  UFirstSelectMode::FinishedSession(bool ok)
{
	Session->OnFindSessionsCompleteDelegates.RemoveAll(this);

	auto LocalId = GetLocalIdSafe();
	if (!LocalId.IsValid()) { UE_LOG(LogTemp, Error, TEXT("LocalId invalid")); return; }

	TArray<FOnlineSessionSearchResult> Candidates;
	if (ok && Search.IsValid()) {
		for (const auto& R : Search->SearchResults) {
			if (R.IsValid()) { Candidates.Add(R); break; }
		}
	}

	if (Candidates.Num() > 0)
	{
		Session->OnJoinSessionCompleteDelegates.RemoveAll(this);
		Session->OnJoinSessionCompleteDelegates.AddUObject(this, &UFirstSelectMode::JoinSessionComplete);
		Session->JoinSession(*LocalId, NAME_GameSession, Candidates[0]);
		return;
	}
	if (FindRetries < MaxFindRetries)
	{
		FindRetries++;
		FTimerHandle H;
		GetWorld()->GetTimerManager().SetTimer(H, [this, LocalId]()
			{
				Search = MakeShared<FOnlineSessionSearch>();
				Search->bIsLanQuery = true;
				Search->MaxSearchResults = 50;
				Search->TimeoutInSeconds = 5.0f;

				Session->OnFindSessionsCompleteDelegates.RemoveAll(this);
				Session->OnFindSessionsCompleteDelegates.AddUObject(this, &UFirstSelectMode::FinishedSession);
				Session->FindSessions(*LocalId, Search.ToSharedRef());
			}, FindRetryDelay, false);
		return;
	}

	if (Session->GetNamedSession(NAME_GameSession) != nullptr)
	{
		Session->OnDestroySessionCompleteDelegates.RemoveAll(this);
		Session->OnDestroySessionCompleteDelegates.AddUObject(this, &UFirstSelectMode::OnDestroyThenCreate);
		Session->DestroySession(NAME_GameSession);
		return;
	}
	CreateLanSession();
}

void UFirstSelectMode::OnDestroyThenCreate(FName, bool bOk)
{
	Session->OnDestroySessionCompleteDelegates.RemoveAll(this);
	CreateLanSession();
}
void UFirstSelectMode::CreateLanSession()
{
	if (!Session.IsValid()) return;

	FOnlineSessionSettings s;
	s.bIsLANMatch = true;
	s.bShouldAdvertise = true;
	s.NumPublicConnections = 2;
	s.bAllowJoinInProgress = true;

	Session->OnCreateSessionCompleteDelegates.RemoveAll(this);
	Session->OnCreateSessionCompleteDelegates.AddUObject(this, &UFirstSelectMode::CreateSessionComplete);

	auto LocalId = GetLocalIdSafe();
	if (!LocalId.IsValid()) { UE_LOG(LogTemp, Error, TEXT("LocalId invalid")); return; }

	Session->CreateSession(*LocalId, NAME_GameSession, s);
}
TSharedPtr<const FUniqueNetId> UFirstSelectMode::GetLocalIdSafe()
{
	if (auto OSS = IOnlineSubsystem::Get()) {
		auto Identity = OSS->GetIdentityInterface();
		if (Identity.IsValid()) 
			return 
		Identity->GetUniquePlayerId(0);
	}
	return nullptr;
}
void  UFirstSelectMode::CreateSessionComplete(FName, bool ok)
{
	Session->OnCreateSessionCompleteDelegates.RemoveAll(this);
	if (!ok)
		return;
	UGameplayStatics::OpenLevel(GetWorld(), FName("/Game/Virtual_Studio_Kit/Maps/Room"), true, TEXT("listen"));
}
void  UFirstSelectMode::JoinSessionComplete(FName, EOnJoinSessionCompleteResult::Type res)
{
	Session->OnJoinSessionCompleteDelegates.RemoveAll(this);
	if (res != EOnJoinSessionCompleteResult::Success)
		return;
	FString add;
	if (Session->GetResolvedConnectString(NAME_GameSession, add))
	{
		if (add.EndsWith(TEXT(":0")))
		{
			int32 Port = 7777;
			GConfig->GetInt(TEXT("/Script/Engine.Engine"), TEXT("DefaultPort"), Port, GEngineIni); 
			GConfig->GetInt(TEXT("URL"), TEXT("Port"), Port, GEngineIni);

			int32 ColonIdx;
			if (add.FindLastChar(':', ColonIdx))
			{
				add = add.Left(ColonIdx) + TEXT(":") + FString::FromInt(Port);
			}
		}

		if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			PC->ClientTravel(add, TRAVEL_Absolute);
		}
	}
}