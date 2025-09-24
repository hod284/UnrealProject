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

	auto localid = GEngine->GetFirstGamePlayer(GetWorld())->GetPreferredUniqueNetId();
	if (ok && Search.IsValid() && Search->SearchResults.Num() > 0)
	{
		Session->OnJoinSessionCompleteDelegates.AddUObject(this, &UFirstSelectMode::JoinSessionComplete);
		Session->JoinSession(*localid, NAME_GameSession, Search->SearchResults[0]);
		return;
	}
	FOnlineSessionSettings s;
	s.bIsLANMatch = Search->bIsLanQuery;
	s.bShouldAdvertise = true;
	s.NumPublicConnections = 2;
	s.bAllowJoinInProgress = true;
	s.bUsesPresence = true;
	Session->OnCreateSessionCompleteDelegates.AddUObject(this, &UFirstSelectMode::CreateSessionComplete);
	Session->DestroySession(NAME_GameSession);
	Session->CreateSession(*localid, NAME_GameSession, s);
}

void  UFirstSelectMode::CreateSessionComplete(FName, bool ok)
{
	Session->OnCreateSessionCompleteDelegates.RemoveAll(this);
	if (!ok)
		return;
	GetWorld()->ServerTravel("/Game/Virtual_Studio_Kit/Maps/Room?listen");
}
void  UFirstSelectMode::JoinSessionComplete(FName, EOnJoinSessionCompleteResult::Type res)
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