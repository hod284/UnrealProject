// Fill out your copyright notice in the Description page of Project Settings.


#include "UImanager.h"

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


}
