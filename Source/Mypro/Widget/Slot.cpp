// Fill out your copyright notice in the Description page of Project Settings.


#include "Slot.h"

void USlot::NativeConstruct()
{
	Super::NativeConstruct();
	Image = Cast<UImage>(GetWidgetFromName(TEXT("Ima")));
	
}
void USlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}
void USlot::NativeDestruct()
{
	Super::NativeDestruct();

}
void USlot::Inite(UTexture2D *im)
{
	Image ->SetBrushFromTexture(im); 

}