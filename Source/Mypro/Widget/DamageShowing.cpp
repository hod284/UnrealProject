// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageShowing.h"

void UDamageShowing::NativeConstruct()
{
	Super::NativeConstruct();
	Damageshwoing = Cast<UTextBlock>(GetWidgetFromName("da"));
 
}

void UDamageShowing::SetDamag(float da)
{
	int32 a = FMath::RoundToInt(da);
	Damageshwoing->SetText(FText::FromString(FString::FromInt(a)));
}
