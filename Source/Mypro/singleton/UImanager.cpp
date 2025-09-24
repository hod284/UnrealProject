// Fill out your copyright notice in the Description page of Project Settings.


#include "UImanager.h"

void UUImanager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	// Initialize the UI manager here, if needed
	if (IntroMainUI)
		IntroMainUI_widget = CreateWidget<UUserWidget>(GetWorld(), IntroMainUI);
	
	if (PlayMainUI)
		PlayMainUI_widget = CreateWidget<UUserWidget>(GetWorld(), PlayMainUI);

	if (WinerUI)
		Winer_widget = CreateWidget<UUserWidget>(GetWorld(), WinerUI);
	if (RoomUI)
		Room_widget = CreateWidget<UUserWidget>(GetWorld(), RoomUI);
	if (PvPUI)
		PvP_widget = CreateWidget<UUserWidget>(GetWorld(), PvPUI);
	if (PartyRoomUI)
		PartyRoom_widget = CreateWidget<UUserWidget>(GetWorld(), PartyRoomUI);
}

UUImanager::UUImanager()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass_intro(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/widget/IntroMainUIWidget.IntroMainUIWidget_C'"));
	if (WidgetClass_intro.Succeeded())
	{
		IntroMainUI = WidgetClass_intro.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass_play(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/widget/PlayMainUIWidget.PlayMainUIWidget_C'"));
	if (WidgetClass_play.Succeeded())
	{
		PlayMainUI = WidgetClass_play.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass_WINER(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/widget/winerWidget.winerWidget_C'"));
	if (WidgetClass_WINER.Succeeded())
	{
		WinerUI = WidgetClass_WINER.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> Room(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/widget/RoomWidget.RoomWidget_C'"));
	if (Room.Succeeded())
	{
		RoomUI = Room.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> PVPClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/widget/PVPMainWidget.PVPMainWidget_C'"));
	if (PVPClass.Succeeded())
	{
		PvPUI = PVPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> PartyRoomClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/widget/PartyRoomWidget.PartyRoomWidget_C'"));
	if (PartyRoomClass.Succeeded())
	{
		PartyRoomUI = PartyRoomClass.Class;
	}
}
