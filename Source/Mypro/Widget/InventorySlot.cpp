// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"

void UInventorySlot::NativeConstruct()
{
    Super::NativeConstruct();
    Icon = Cast<UImage>(GetWidgetFromName(TEXT("ic")));
    Countst = Cast<UTextBlock>(GetWidgetFromName(TEXT("number")));
}

void UInventorySlot::NativeDestruct()
{
}

FReply UInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton && NotEmpty)
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	return  Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UInventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
    USlot* Visual = CreateWidget<USlot>(GetWorld(), SlotClass);
    Visual->TakeWidget();
    Visual->Inite(Cast<UTexture2D>(Icon->GetBrush().GetResourceObject()));
    UMyDragDropOperation* DragOp = Cast<UMyDragDropOperation>(
        UWidgetBlueprintLibrary::CreateDragDropOperation(UMyDragDropOperation::StaticClass()));
    FString str = Countst->GetText().ToString();
    DragOp->Itemname = Itemname;
    DragOp->Count = str;
    DragOp->Texture = Cast<UTexture2D>(Icon->GetBrush().GetResourceObject());
    DragOp->SourceSlot = this;
    DragOp->DefaultDragVisual = Visual;
    OutOperation = DragOp;
}

bool UInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    if (UMyDragDropOperation* Op = Cast<UMyDragDropOperation>(InOperation))
    {
        // 예: 실제 인벤토리 로직에 반영
        FString co = Op->Count;
        SetTexture(Op->Texture);
        Settext(co);
        SetNotEmpty(true);
        Op->SourceSlot->SetTexture(NULL);
        Op->SourceSlot->Settext("0");
        Op->SourceSlot->SetNotEmpty(false);
        return true;
    }
	return false;
}

void UInventorySlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
}
void UInventorySlot::Init(UTexture2D *im, int32 Count, FString name)
{
    Icon->SetBrushFromTexture(im);
    FString s = FString::FromInt(Count);
    Countst->SetText(FText::FromString(s));
    Itemname = name;
}

void UInventorySlot::SetTexture(UTexture2D* im)
{
    Icon->SetBrushFromTexture(im);
}
void UInventorySlot::Settext(FString Count)
{
    if (Count == "0")
    {
        Icon->SetBrushFromTexture(NULL);
        NotEmpty = false;
        Countst->SetText(FText::GetEmpty());
    }
    else
    Countst->SetText(FText::FromString(Count));
}

UInventorySlot::UInventorySlot(const FObjectInitializer& ObjectInitializer):
    UUserWidget(ObjectInitializer)
{
    static ConstructorHelpers::FClassFinder<UUserWidget> slotc(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/widget/slotwidget.slotwidget_C'"));
    if (slotc.Succeeded())
        SlotClass = slotc.Class;
}
