// Fill out your copyright notice in the Description page of Project Settings.


#include "CharterChoice.h"

void UCharterChoice::NativeConstruct()
{
	back->OnClicked.AddDynamic(this, &UCharterChoice::Backclick);
}

void UCharterChoice::Backclick()
{
	UIntroMainUI* ui = Cast<UIntroMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetIntroMainUI_widget());
	if (ui)
	{
		ui->SetSwitcherIndex(0);
	}
}
