// Fill out your copyright notice in the Description page of Project Settings.


#include "WinerWidgetClass.h"

void UWinerWidgetClass::NativeConstruct()
{
	Winner = Cast<UTextBlock>(GetWidgetFromName("Title"));
	GotoIntro = Cast<UButton>(GetWidgetFromName("Go"));
	Gameexit = Cast<UButton>(GetWidgetFromName("exit"));
	GetWorld()->GetTimerManager().ClearTimer(Timer);
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &UWinerWidgetClass::Typing, 0.5f, true);
	GotoIntro->OnClicked.AddDynamic(this, &UWinerWidgetClass::Gotointromethod);
	Gameexit->OnClicked.AddDynamic(this, &UWinerWidgetClass::GotoExit);
}

void UWinerWidgetClass::NativeOnInitialized()
{
}

void UWinerWidgetClass::Typing()
{
	TimeCount += 1;
	switch (TimeCount)
	{
		case 1:
			Winner->SetText(FText::FromString("W"));
			break;
		case 2:
			Winner->SetText(FText::FromString("W "));
			break;
		case 3:
			Winner->SetText(FText::FromString("W I"));
			break;
		case 4:
			Winner->SetText(FText::FromString("W I "));
			break;
		case 5:
			Winner->SetText(FText::FromString("W I N"));
			break;
		case 6:
			Winner->SetText(FText::FromString("W I N E"));
			break;
		case 7:
			Winner->SetText(FText::FromString("W I N E "));
			break;
		case 8:
			Winner->SetText(FText::FromString("W I N E R"));
			break;
		case 9:
			TimeCount=0;
			GetWorld()->GetTimerManager().ClearTimer(Timer);
			break;
	default:
		break;
	}
}

void UWinerWidgetClass::Gotointromethod()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Virtual_Studio_Kit/Maps/StudioC"));
}

void UWinerWidgetClass::GotoExit()
{
	UKismetSystemLibrary::QuitGame(
		GetWorld(),
		GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit,
		false   // bIgnorePlatformRestrictions
	);
}
