 // Fill out your copyright notice in the Description page of Project Settings.


#include "Aurora.h"

AAurora::AAurora()
{

}

void AAurora::BeginPlay()
{
    Super::BeginPlay();
    UMySingleton* GI = Cast<UMySingleton>(UGameplayStatics::GetGameInstance(GetWorld()));
  Info =  GI->GetDatainfo_W();
  PlayerHp = static_cast<float>(Info->HP);
  PlayerMp = static_cast<float>(Info->MP);
  PlayerHp_Const = PlayerHp;
  PlayerMp_Const = PlayerMp;
  AttackDamage = Info->ATK;
  AttackDamageUp = Info->Skill3_ATK;
}
void AAurora::NAttack()
{
    TArray<FHitResult>	result;

    FCollisionQueryParams	param;
    param.AddIgnoredActor(this);
    param.bTraceComplex = false;
    float Radious = 100.0f;
    FVector center = GetActorLocation()+CurrentVelocity * 100;
    bool Collision;
	ECollisionChannel channel = ECollisionChannel::ECC_GameTraceChannel2;
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
    {
         channel = ECollisionChannel::ECC_GameTraceChannel2;
    }
    else  if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
    {
            channel = ECollisionChannel::ECC_GameTraceChannel3;
    }
    Collision = GetWorld()->SweepMultiByChannel(result, center, center,
        FQuat::Identity,channel,
        FCollisionShape::MakeCapsule(Radious, 200), param);
    DrawDebugCapsule(GetWorld(), center, 200, Radious, FQuat::Identity, FColor::Green, false, 2.f);
    float pe = static_cast<float>(AttackDamage);
    if (Collision)
    {
        float	Origin = FMath::Cos(FMath::DegreesToRadians(45.f));

        for (auto& Hit : result)
        {
            if (Hit.GetActor()->IsA<APawn>())
            {
                AddMpbar(10);
                if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
                UGameplayStatics::ApplyDamage(Hit.GetActor(), pe, GetInstigatorController(), this, UDamageType::StaticClass());
                else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
                {
                    if (!HasAuthority())
                        UGameplayStatics::ApplyDamage(Hit.GetActor(), pe, GetInstigatorController(), this, UDamageType::StaticClass());
                    else
                    {
                        PlayerController->Server_SendtheDamage(Hit.GetActor(), pe);
                    }
                }
            }
        }
    }
}

void AAurora::Skill1()
{
    Skill1coolTime(0.5f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
    FRotator SpawnRotation = FRotator::ZeroRotator;
    if(GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
        SpawnRotation =  FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    else if(GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
    {
        if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
        {
            SpawnRotation=   FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
        }
        else if (PlayerController&& PlayerController->IsLocalController() && !HasAuthority())
        {
            SpawnRotation=  FRotator(0, (GetMesh()->GetRelativeRotation().Yaw- GetActorRotation().Yaw)-90, 0);
        }
    }
    FRotator SpawnRotationShowing = SpawnRotation;
    FVector  Loc = SpawnLocation;
    FRotator Rot = SpawnRotationShowing;
    FVector  Scl = FVector(1, 1, 1);
    FTransform Xform(Rot, Loc, Scl);
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
    {
        A1 = GetWorld()->SpawnActorDeferred<ASkill1_Actor>(Sk1, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
        A1->SetAttackDamage(Info->Skill1_ATK);
        A1->IngoreActor(this);
        UGameplayStatics::FinishSpawningActor(A1, Xform);
    }
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
    {
        if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
            Multicast_PlaySkill1(Xform);
        else  if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
            Server_PlaySkill1(Xform);
    }
    MpbarSync(10.0F);
}

void AAurora::Skill2()
{
    Skill2coolTime(0.4f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
    FRotator SpawnRotation = FRotator::ZeroRotator;
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
        SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
    {
        if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
        {
            SpawnRotation =FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
        }
        else if (PlayerController&&PlayerController->IsLocalController() && !HasAuthority())
        {
            SpawnRotation = FRotator(0, (GetMesh()->GetRelativeRotation().Yaw - GetActorRotation().Yaw) - 90, 0);
        }
    }
    FRotator SpawnRotationShowing = SpawnRotation;
    FVector  Loc = SpawnLocation;
    FRotator Rot = SpawnRotationShowing;
    FVector  Scl = FVector(1, 1, 1);
    FTransform Xform(Rot, Loc, Scl);
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
    {
        A2 = GetWorld()->SpawnActorDeferred<ASkill2_Actor>(Sk2, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
        A2->SetAttackDamage(Info->Skill2_ATK);
        A2->IngoreActor(this);
        UGameplayStatics::FinishSpawningActor(A2, Xform);
    }
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
    {
        if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
            Multicast_PlaySkill2(Xform);
        else  if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
            Server_PlaySkill2(Xform);
    }
    MpbarSync(10.0F);
}

void AAurora::Skill3()
{
     Skill3coolTime(0.2f);
     AttackDamage += AttackDamageUp;
     if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
     {
         GetMesh()->SetOverlayMaterial(Mat);
         Niagara->SetVisibility(true);
     }
     else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
     {
         if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
             Multicast_PlaySkill3();
         else  if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
             Server_PlaySkill3();
     }
     MpbarSync(10.0F);
}

void AAurora::Skill4()
{
    Skill4coolTime(0.1f);
    FVector SpawnLocation = FVector(TargetLocation.X, TargetLocation.Y, 0);
    FRotator SpawnRotation = FRotator::ZeroRotator;
    FVector  Loc = SpawnLocation;
    FRotator Rot = SpawnRotation;
    FVector  Scl = FVector(1, 1, 1);
    FTransform Xform(Rot, Loc, Scl);
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
    {
        A4 = GetWorld()->SpawnActorDeferred<ASkill4_Actor>(Sk4, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
        A4->SetAttackDamage(Info->Skill4_ATK);
        A4->IngoreActor(this);
        UGameplayStatics::FinishSpawningActor(A4, Xform);
    }
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
    {
        if (PlayerController && PlayerController->IsLocalController()&&HasAuthority())
            Multicast_PlaySkill4(Xform);
        else if (PlayerController && PlayerController->IsLocalController()&&!HasAuthority())
            Server_PlaySkill4(Xform);
    }
    MpbarSync(10.0F);
}

void AAurora::Multicast_PlaySkill1_Implementation(FTransform form)
{
    A1 = GetWorld()->SpawnActorDeferred<ASkill1_Actor>(Sk1, form, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A1->SetAttackDamage(Info->Skill1_ATK);
    A1->IngoreActor(this);
    UGameplayStatics::FinishSpawningActor(A1, form);
}

void AAurora::Server_PlaySkill1_Implementation(FTransform form)
{
    Multicast_PlaySkill1(form);
}

void AAurora::Multicast_PlaySkill2_Implementation(FTransform form)
{
    A2 = GetWorld()->SpawnActorDeferred<ASkill2_Actor>(Sk2, form, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A2->SetAttackDamage(Info->Skill2_ATK);
    A2->IngoreActor(this);
    UGameplayStatics::FinishSpawningActor(A2, form);
}

void AAurora::Server_PlaySkill2_Implementation(FTransform form)
{
    Multicast_PlaySkill2(form);
}

void AAurora::Multicast_PlaySkill3_Implementation()
{
    GetMesh()->SetOverlayMaterial(Mat);
    Niagara->SetVisibility(true);
}

void AAurora::Server_PlaySkill3_Implementation()
{
    Multicast_PlaySkill3();
}

void AAurora::Multicast_PlaySkill4_Implementation(FTransform form)
{
    A4 = GetWorld()->SpawnActorDeferred<ASkill4_Actor>(Sk4, form, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A4->SetAttackDamage(Info->Skill4_ATK);
    A4->IngoreActor(this);
    UGameplayStatics::FinishSpawningActor(A4, form);
}

void AAurora::Server_PlaySkill4_Implementation(FTransform form)
{
    Multicast_PlaySkill4(form);
}
