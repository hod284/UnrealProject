// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomWidgetClass.h"
void  URoomWidgetClass::NativeConstruct()
{
	Super::NativeConstruct();
	Character1 = Cast<UButton>(GetWidgetFromName("ch1"));
	Character2 = Cast<UButton>(GetWidgetFromName("ch2"));
	Character3 = Cast<UButton>(GetWidgetFromName("ch3"));
	Muteb = Cast<UButton>(GetWidgetFromName("Mute"));
	Ready = Cast<UButton>(GetWidgetFromName("Ready"));
	Start = Cast<UButton>(GetWidgetFromName("Start"));
	if (!Character1->OnClicked.IsBound())
		Character1->OnClicked.AddDynamic(this, &URoomWidgetClass::Character1Click);
	if (!Character2->OnClicked.IsBound())
		Character2->OnClicked.AddDynamic(this, &URoomWidgetClass::Character2Click);
	if (!Character3->OnClicked.IsBound())
		Character3->OnClicked.AddDynamic(this, &URoomWidgetClass::Character3Click);
	if (!Ready->OnClicked.IsBound())
		Ready->OnClicked.AddDynamic(this, &URoomWidgetClass::ReadyButton);
	if (!Start->OnClicked.IsBound())
		Start->OnClicked.AddDynamic(this, &URoomWidgetClass::GoTravel);
	if (!Muteb->OnClicked.IsBound())
		Muteb->OnClicked.AddDynamic(this, &URoomWidgetClass::AudioMutemethod);
	UMySingleton* GI = Cast<UMySingleton>(UGameplayStatics::GetGameInstance(GetWorld()));
	PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	Start->SetVisibility(ESlateVisibility::Collapsed);
	Character1Click();
}
void URoomWidgetClass::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry,InDeltaTime);
	if (PC->HasAuthority())
	{
		AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
		UE_LOG(LogMypro, Warning, TEXT("bool°©%s"), (PS->Ready_H ? TEXT("true") : TEXT("false")));
		UE_LOG(LogMypro, Warning, TEXT("bool°ªH%s"), (PS->Ready_C ?TEXT("true") : TEXT("false")));
		if(PS->Ready_H&& PS->Ready_C)
		Start->SetVisibility(ESlateVisibility::Visible);
	}
}
void URoomWidgetClass::NativeOnInitialized()
{
}

void  URoomWidgetClass::Character1Click()
{
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetSelectCharacter(Characters::Warrior);
	UMySingleton* GI = Cast<UMySingleton>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (PC->HasAuthority())
	{
		APlayerController* PCfirst = GetWorld()->GetFirstPlayerController();
		AMyPlayerState* PS = Cast<AMyPlayerState>(PCfirst->PlayerState);
		PS->Pitch_H = 0;
		PS->MyCharacter_H = Characters::Warrior;
	}
	else
	{
		PC->Sever_SendtheRotate(0);
		PC->Server_SetSelectedPawn(Characters::Warrior);
	}
}

void  URoomWidgetClass::Character2Click()
{
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetSelectCharacter(Characters::Guiden);
	UMySingleton* GI = Cast<UMySingleton>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (PC->HasAuthority())
	{
		APlayerController* PCfirst = GetWorld()->GetFirstPlayerController();
		AMyPlayerState* PS = Cast<AMyPlayerState>(PCfirst->PlayerState);
		 PS->Pitch_H =-90;
		 PS->MyCharacter_H = Characters::Guiden;
	}
	else
	{

		PC->Sever_SendtheRotate(-90);
		PC->Server_SetSelectedPawn(Characters::Guiden);
	}
}

void  URoomWidgetClass::Character3Click()
{
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetSelectCharacter(Characters::DarkMagion);
	UMySingleton* GI = Cast<UMySingleton>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (PC->HasAuthority())
	{
		APlayerController* PCfirst = GetWorld()->GetFirstPlayerController();
		AMyPlayerState* PS = Cast<AMyPlayerState>(PCfirst->PlayerState);
		PS->Pitch_H = -180;
		PS->MyCharacter_H = Characters::DarkMagion;
	}
	else
	{
		PC->Sever_SendtheRotate(-180);
		PC->Server_SetSelectedPawn(Characters::DarkMagion);
	}
}
void URoomWidgetClass::ReadyButton()
{
	if (PC->HasAuthority())
	{
		APlayerController* FirstPC = GetWorld()->GetFirstPlayerController();
		AMyPlayerState* PS = Cast<AMyPlayerState>(FirstPC->PlayerState);
		PS->Ready_H = true;
	}
	else
	{
		PC->Sever_SendtheReady(true);
	}
	Character1->SetVisibility(ESlateVisibility::Collapsed);
	Character2->SetVisibility(ESlateVisibility::Collapsed);
	Character3->SetVisibility(ESlateVisibility::Collapsed);
	Ready->SetVisibility(ESlateVisibility::Collapsed);
}
void URoomWidgetClass::GoTravel()
{
	GetWorld()->ServerTravel("/Game/Virtual_Studio_Kit/Maps/StudioB?listen");
}

void URoomWidgetClass::AudioMutemethod()
{
	if (SoundComp->IsPlaying())
		SoundComp->Stop();
	else
		SoundComp->Play();
}
