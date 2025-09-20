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
	LoseTyping = Cast<UTextBlock>(GetWidgetFromName("Lose"));
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
	APlayerController* PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PC->IsLocalController())
	{
		Skill1->SetTIme(Percent1);
		Skill2->SetTIme(Percent2);
		Skill3->SetTIme(Percent3);
		Skill4->SetTIme(Percent4);
	}
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
		FString co = Op->Count;
		Op->SourceSlot->SetTexture(NULL);
		Op->SourceSlot->Settext("0");
		Op->SourceSlot->SetNotEmpty(false);
		APlayerController* PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
		AMyPlayerState* PS  = Cast<AMyPlayerState>(PC->PlayerState);
		if (IsValid( PS) )
			PS->Inventoryco->ItemMinus.Broadcast(Op->SourceSlot->GetName());
		Op->SourceSlot->SetName("");
		// 1) ���� ��ũ����ǥ �� ����Ʈ ��ǥ
		FVector2D Abs = InDragDropEvent.GetScreenSpacePosition();
		FGeometry ViewGeom = UWidgetLayoutLibrary::GetViewportWidgetGeometry(this);
		FVector2D ViewPos = ViewGeom.AbsoluteToLocal(Abs);

		// 2) ����Ʈ ��ǥ �� ���� ������/����
		FVector Origin, Dir;
		PC->DeprojectScreenPositionToWorld(ViewPos.X, ViewPos.Y, Origin, Dir);

		// 3) �缱(�밢)���� ���� ����̱�
		//    ��: �������� Yaw +20��, ���� Pitch +10�� ���ø���
		 float YawDeg = -40.f;  // ��(-) / ��(+)
		 float PitchDeg = -10.f;  // ��(-) / �Ʒ�(+), Rotator ��Ģ ����
		 FRotator DeltaRot(PitchDeg, YawDeg, 0.f);
		 FVector  DiagDir = DeltaRot.RotateVector(Dir).GetSafeNormal();

		// 4) Ʈ���̽�(���� ���߰� ������ ä��/������Ʈ Ÿ�� ����)
		 float MaxDist = 200000.f;
		 FVector Start = Origin;
		 FVector End = Start + DiagDir * MaxDist;

		FHitResult Hit;
		FCollisionQueryParams Params(SCENE_QUERY_STAT(DropDiagTrace), /*bTraceComplex=*/true);
		if (APawn* Pawn = PC->GetPawn()) Params.AddIgnoredActor(Pawn);

		// (A) ������: ���ü� ä��
		bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

		// (B) ���鸸: ���彺��ƽ�� ���߱�
		// FCollisionObjectQueryParams Obj;
		// Obj.AddObjectTypesToQuery(ECC_WorldStatic);
		// bool bHit = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, Obj, Params);

		// �����
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.f, 0, 1.f);

		if (!bHit) 
			return false;

		FVector SpawnLoc =  Hit.Location;
		FRotator SpawnRot = FRotator::ZeroRotator;
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		AStaticMeshActor* MeshActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), SpawnLoc, SpawnRot,param);
		MeshActor->Rename(TEXT("Portal2"));
		if (MeshActor)
		{
			MeshActor->SetMobility(EComponentMobility::Movable);
			UMySingleton* GI = Cast<UMySingleton>(UGameplayStatics::GetGameInstance(GetWorld()));
			const FItmeTexturAndMeshInfo* Texture = GI->GetTextureInfo();
			UStaticMesh* Mesh = Texture->MeshMap["Portal"];
			MeshActor->GetStaticMeshComponent()->SetStaticMesh(Mesh);
			MeshActor->SetActorScale3D(FVector(1.0f)); 
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
void UPlayMainUI::SkillInite()
{
	switch (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSelectedcharacter())
	{
	case Characters::DarkMagion:
		SetSkill1Inite(TEXT("/Game/image/m1.m1"));
		SetSkill2Inite(TEXT("/Game/image/m2.m2"));
		SetSkill3Inite(TEXT("/Game/image/m3.m3"));
		SetSkill4Inite(TEXT("/Game/image/m4.m4"));
		SetPlayerImage(TEXT("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/giden.giden"));
		break;
	case Characters::Guiden:
		SetSkill1Inite(TEXT("/Game/image/1.1"));
		SetSkill2Inite(TEXT("/Game/image/2.2"));
		SetSkill3Inite(TEXT("/Game/image/3.3"));
		SetSkill4Inite(TEXT("/Game/image/4.4"));
		SetPlayerImage(TEXT("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/greyston.greyston"));
		break;
	case Characters::Warrior:
		SetSkill1Inite(TEXT("/Game/image/1.1"));
		SetSkill2Inite(TEXT("/Game/image/2.2"));
		SetSkill3Inite(TEXT("/Game/image/3.3"));
		SetSkill4Inite(TEXT("/Game/image/4.4"));
		SetPlayerImage(TEXT("/Game/Virtual_Studio_Kit/Textures/Paragon/Heros_1024/Auraura.Auraura"));
		break;
	default:
		break;
	}
}

void UPlayMainUI::Typing()
{
	TimeCount += 1;
	switch (TimeCount)
	{
	case 1:
		LoseTyping->SetText(FText::FromString("L"));
		break;
	case 2:
		LoseTyping->SetText(FText::FromString("L "));
		break;
	case 3:
		LoseTyping->SetText(FText::FromString("L O"));
		break;
	case 4:
		LoseTyping->SetText(FText::FromString("L O "));
		break;
	case 5:
		LoseTyping->SetText(FText::FromString("L O S"));
		break;
	case 6:
		LoseTyping->SetText(FText::FromString("L O S "));
		break;
	case 7:
		LoseTyping->SetText(FText::FromString("L O S E"));
		break;
	case 9:
		TimeCount = 0;
		GetWorld()->GetTimerManager().ClearTimer(Timer);
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Virtual_Studio_Kit/Maps/StudioC"));
		break;
	default:
		break;
	}
}

void UPlayMainUI::TypingStart()
{
	GetWorld()->GetTimerManager().ClearTimer(Timer);
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &UPlayMainUI::Typing, 0.5f, true);
}
