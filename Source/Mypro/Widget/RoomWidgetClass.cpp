// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomWidgetClass.h"
void  URoomWidgetClass::NativeConstruct()
{
	Super::NativeConstruct();
	Character1 = Cast<UButton>(GetWidgetFromName("ch1"));
	Character2 = Cast<UButton>(GetWidgetFromName("ch2"));
	Character3 = Cast<UButton>(GetWidgetFromName("ch3"));
	skill1 = Cast<UButton>(GetWidgetFromName("skill1b"));
	skill2 = Cast<UButton>(GetWidgetFromName("skill2b"));
	skill3 = Cast<UButton>(GetWidgetFromName("skill3b"));
	skill4 = Cast<UButton>(GetWidgetFromName("skill4b"));
	skill1_MA = Cast<UButton>(GetWidgetFromName("skill1b_ma"));
	skill2_MA = Cast<UButton>(GetWidgetFromName("skill2b_ma"));
	skill3_MA = Cast<UButton>(GetWidgetFromName("skill3b_ma"));
	skill4_MA = Cast<UButton>(GetWidgetFromName("skill4b_ma"));
	if (!Character1->OnClicked.IsBound())
		Character1->OnClicked.AddDynamic(this, &URoomWidgetClass::Character1Click);
	if (!Character2->OnClicked.IsBound())
		Character2->OnClicked.AddDynamic(this, &URoomWidgetClass::Character2Click);
	if (!Character3->OnClicked.IsBound())
		Character3->OnClicked.AddDynamic(this, &URoomWidgetClass::Character3Click);
	UMySingleton* GI = Cast<UMySingleton>(UGameplayStatics::GetGameInstance(GetWorld()));
	PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}
void URoomWidgetClass::NativeOnInitialized()
{
}

void  URoomWidgetClass::Character1Click()
{
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetSelectCharacter(Characters::Warrior);
	CharacterButtonChoice(Characters::Warrior);
	UMySingleton* GI = Cast<UMySingleton>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (PC->HasAuthority())
	{
		PC->SendtheRotate(0);
	}
	else
	{
		PC->Sever_SendtheRotate(0);
	}
}

void  URoomWidgetClass::Character2Click()
{
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetSelectCharacter(Characters::Guiden);
	CharacterButtonChoice(Characters::Guiden);
	UMySingleton* GI = Cast<UMySingleton>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (PC->HasAuthority())
	{
		PC->SendtheRotate(-90);
	}
	else
	{

		PC->Sever_SendtheRotate(-90);
	}
}

void  URoomWidgetClass::Character3Click()
{
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetSelectCharacter(Characters::DarkMagion);
	CharacterButtonChoice(Characters::DarkMagion);
	UMySingleton* GI = Cast<UMySingleton>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (PC->HasAuthority())
	{
		PC->SendtheRotate(-180);
	}
	else
	{
		PC->Sever_SendtheRotate(-180);
	}
}
void URoomWidgetClass::CharacterButtonChoice(Characters ch)
{

	if (ch == Characters::DarkMagion)
	{
		skill1_MA->SetVisibility(ESlateVisibility::Visible);
		skill2_MA->SetVisibility(ESlateVisibility::Visible);
		skill3_MA->SetVisibility(ESlateVisibility::Visible);
		skill4_MA->SetVisibility(ESlateVisibility::Visible);
		skill1->SetVisibility(ESlateVisibility::Collapsed);
		skill2->SetVisibility(ESlateVisibility::Collapsed);
		skill3->SetVisibility(ESlateVisibility::Collapsed);
		skill4->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		skill1_MA->SetVisibility(ESlateVisibility::Collapsed);
		skill2_MA->SetVisibility(ESlateVisibility::Collapsed);
		skill3_MA->SetVisibility(ESlateVisibility::Collapsed);
		skill4_MA->SetVisibility(ESlateVisibility::Collapsed);
		skill1->SetVisibility(ESlateVisibility::Visible);
		skill2->SetVisibility(ESlateVisibility::Visible);
		skill3->SetVisibility(ESlateVisibility::Visible);
		skill4->SetVisibility(ESlateVisibility::Visible);
	}
}
