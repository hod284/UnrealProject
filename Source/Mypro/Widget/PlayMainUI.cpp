// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayMainUI.h"
#include"../player/MyPlayerState.h"
#include "../common/PlaySceneObject.h"
void UPlayMainUI::NativeConstruct()
{
	Super::NativeConstruct();
	Skill1 = Cast<USkillStatus>(GetWidgetFromName("SkillUI1"));
	Skill2 = Cast<USkillStatus>(GetWidgetFromName("SkillUI2"));
	Skill3 = Cast<USkillStatus>(GetWidgetFromName("SkillUI3"));
	Skill4 = Cast<USkillStatus>(GetWidgetFromName("SkillUI4"));
	PlayerImage = Cast<UImage>(GetWidgetFromName("Playerimg"));
	PlayerHp =Cast<UProgressBar>(GetWidgetFromName("PlayerHP"));
	PlayerMp = Cast<UProgressBar>(GetWidgetFromName("PlayerMP"));
	MonsterHp = Cast<UProgressBar>(GetWidgetFromName("MHP"));
	MonsterStun = Cast<UProgressBar>(GetWidgetFromName("MST"));
	Inventory = Cast<UInventory>(GetWidgetFromName("Inven"));
	Inventory->SetVisibility(ESlateVisibility::Collapsed);
	if(!OnDamage_M.IsBound())
	FDelegateHandle Handle1 =  OnDamage_M.AddUObject(this,&UPlayMainUI::SetMHpBar);
	if (!OnStunDamage.IsBound())
	FDelegateHandle Handle2  = OnStunDamage.AddUObject(this,&UPlayMainUI::SetStunBar);
	if (!OnDamage_P.IsBound())
	FDelegateHandle Handle3 =  OnDamage_P.AddUObject(this,&UPlayMainUI::SetPHpBar);
	if (!OnSyncMp_P.IsBound())
	FDelegateHandle Handle4 = OnSyncMp_P.AddUObject(this, &UPlayMainUI::SetPMpBar);
	PlayerHp->SetPercent(1.0);
	MonsterStun->SetPercent(1.0);
	MonsterHp->SetPercent(1.0);
	PlayerMp->SetPercent(1.0);
}

UPlayMainUI::UPlayMainUI(const FObjectInitializer& ObjectInitializer):
UUserWidget(ObjectInitializer)
{
}
void UPlayMainUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) 
{
	Super::NativeTick( MyGeometry, InDeltaTime);
	Skill1->SetTIme(Percent1);
	Skill2-> SetTIme(Percent2);
	Skill3->SetTIme(Percent3); 
	Skill4 -> SetTIme(Percent4);
}
void UPlayMainUI::SetStunBar(float da)
{
	MonsterStun->SetPercent(da);
}
void UPlayMainUI::SetMHpBar(float da)
{
	MonsterHp->SetPercent(da);
}
void UPlayMainUI::SetPMpBar(float da)
{
	PlayerMp->SetPercent(da);
}
bool UPlayMainUI::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (UMyDragDropOperation* Op = Cast<UMyDragDropOperation>(InOperation))
	{
		// ��: ���� �κ��丮 ������ �ݿ�
		FString co = Op->Count;
		Op->SourceSlot->SetTexture(NULL);
		Op->SourceSlot->Settext("0");
		Op->SourceSlot->SetNotEmpty(false);
		// GetOwningPlayer()�� createwidget�Ҷ� owner�� ������ ����� null�� ���´� �׷��� ���� ����ؾ� �Ұ�� ������ ����������
		APlayerController* PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
		AMyPlayerState* PS  = Cast<AMyPlayerState>(PC->PlayerState);
		if (IsValid( PS) )
			PS->Inventoryco->ItemMinus.Broadcast(Op->SourceSlot->GetName());
		Op->SourceSlot->SetName("");
		// ��ũ�������� ����
		FVector2D screenposition = InDragDropEvent.GetScreenSpacePosition();
		FHitResult hit;
		// ��ũ��ȭ�鿡�� ���̸� ���� ��Ʈ �ߴ��� ���ߴ��� Ȯ��
		// ��ũ��ȭ�鿡�� ���̸� ���� ��Ʈ �ߴ��� ���ߴ��� Ȯ��
		bool bHit = PC->GetHitResultAtScreenPosition(
			screenposition, ECollisionChannel::ECC_Visibility, /*bTraceComplex=*/true, hit);
		if (!bHit) return false;

		const FVector SpawnLoc = hit.Location;
		const FRotator SpawnRot = FRotator::ZeroRotator;
		AStaticMeshActor* MeshActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), SpawnLoc, SpawnRot);
		MeshActor->Rename(TEXT("Portal"));
		if (MeshActor)
		{
			MeshActor->SetMobility(EComponentMobility::Movable);
			UMySingleton* GI = Cast<UMySingleton>(UGameplayStatics::GetGameInstance(GetWorld()));
			const FItmeTexturAndMeshInfo* Texture = GI->GetTextureInfo();
			UStaticMesh* Mesh = Texture->MeshMap["Portal"];
			MeshActor->GetStaticMeshComponent()->SetStaticMesh(Mesh);
			MeshActor->SetActorScale3D(FVector(1.0f)); // ũ�� ����
		}

		return true;
	}
	return false;
}
void UPlayMainUI::SetPHpBar(float da)
{
	PlayerHp->SetPercent(da);
}
void UPlayMainUI::SetSkill1Inite(FString Path)
{
	Skill1->Setinit(Path, 1);
}
void UPlayMainUI::SetSkill2Inite(FString Path)
{
	Skill2->Setinit(Path, 1);
}
void UPlayMainUI::SetSkill3Inite(FString Path)
{
	Skill3->Setinit(Path, 1);
}
void UPlayMainUI::SetSkill4Inite(FString Path)
{
	Skill4->Setinit(Path, 1);
}
void UPlayMainUI::SetPlayerImage(FString Path)
{
	TSoftObjectPtr<UTexture2D> SoftTexture = TSoftObjectPtr<UTexture2D>(Path);
	PlayerImage->SetBrushFromSoftTexture(SoftTexture);
}