// Fill out your copyright notice in the Description page of Project Settings.


#include "IntroMainUI.h"
#include "../common/IntroSceneObject.h"

void UIntroMainUI::SetSwitcherIndex(int32 Index)
{
	if (Switcher)
	{
		Switcher->SetActiveWidgetIndex(Index);
	}

	laodingtitle->SetVisibility(Index==2? ESlateVisibility::Visible: ESlateVisibility::Collapsed);
	percenttext->SetVisibility(Index == 2 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	Start->SetVisibility(Index == 1 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UIntroMainUI::SetPercenttext(float pe)
{
	float va = pe * 100.0f;
	percenttext->SetText(FText::FromString(FString::Printf(TEXT("%d"), FMath::RoundToInt(va))));
}
void UIntroMainUI::VisuallyStart(ESlateVisibility visible)
{
	Start->SetVisibility(visible);
}

void UIntroMainUI::NativeConstruct()
{
	Super::NativePreConstruct();
	laodingtitle = Cast<UTextBlock>(GetWidgetFromName(TEXT("loadingtitle")));
	percenttext = Cast<UTextBlock>(GetWidgetFromName(TEXT("percent")));
	Start = Cast<UButton>(GetWidgetFromName("Startbutton"));
	Start->OnClicked.AddDynamic(this, &UIntroMainUI::StartButtonClick);
}

void UIntroMainUI::NativeDestruct()
{
	Super::NativeDestruct();

}
void UIntroMainUI::StartButtonClick()
{
	GameStart(GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSelectedcharacter());
}

void UIntroMainUI::GameStart(Characters ch)
{
	AIntroSceneObject* IntroSceneObject = Cast<AIntroSceneObject>(UGameplayStatics::GetActorOfClass(GetWorld(), AIntroSceneObject::StaticClass()));
	if (IntroSceneObject)
		IntroSceneObject->CallthePlayCharacter(ch);
}