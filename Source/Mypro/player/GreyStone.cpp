// Fill out your copyright notice in the Description page of Project Settings.


#include "GreyStone.h"

void AGreyStone::NAttack()
{
    TArray<FHitResult>	result;
    float Radious = 100.0f;
    FCollisionQueryParams	param;
    param.AddIgnoredActor(this);
    param.bTraceComplex = false;
    FVector center = GetActorLocation() + CurrentVelocity * 50;
    DrawDebugCapsule(GetWorld(), center, 200, Radious, FQuat::Identity, FColor::Green, false, 2.f);
    bool Collision = GetWorld()->SweepMultiByChannel(result, center, center,
        FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2,
        FCollisionShape::MakeCapsule(Radious, 200), param);

    if (Collision)
    {
        float	Origin = FMath::Cos(FMath::DegreesToRadians(45.f));

        for (auto& Hit : result)
        {
            if(Hit.GetActor()->IsA<APawn>())
            AddMpbar(10);
            UGameplayStatics::ApplyDamage(Hit.GetActor(), AttackDamage, GetInstigatorController(), this, UDamageType::StaticClass());
        }
    }
}
void AGreyStone::BeginPlay()
{
    Super::BeginPlay();
    UMySingleton* GI = Cast<UMySingleton>(UGameplayStatics::GetGameInstance(GetWorld()));
    Info = GI->GetDatainfo_G();
    PlayerHp = static_cast<float>(Info->HP);
    PlayerMp = static_cast<float>(Info->MP);
    PlayerHp_Const = PlayerHp;
    PlayerMp_Const = PlayerMp;
    AttackDamage = Info->ATK;
    AttackDamageUp = Info->Skill3_ATK;
}
void AGreyStone::Skill1()
{
    Skill1coolTime(0.5f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
    FRotator SpawnRotation = FRotator::ZeroRotator;
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
        SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    else if (PlayerController)
    {
        if (PlayerController->HasAuthority())
        {
            SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
        }
        else if (PlayerController->IsLocalController())
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
        A1 = GetWorld()->SpawnActorDeferred<ASkill1_Actor>(Sk1, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
        A1->SetAttackDamage(Info->Skill1_ATK);
        UGameplayStatics::FinishSpawningActor(A1, Xform);
        MpbarSync(10.0F);
    }
    else if(GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
    {
        if (HasAuthority())
            Multicast_PlaySkill1(Xform);
        else
            Server_PlaySkill1(Xform);
    }
}

void AGreyStone::Skill2()
{
    Skill2coolTime(0.4f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
    FRotator SpawnRotation = FRotator::ZeroRotator;
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
        SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    else if (PlayerController)
    {
        if (PlayerController->HasAuthority())
        {
            SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
        }
        else if (PlayerController->IsLocalController())
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
        UGameplayStatics::FinishSpawningActor(A2, Xform);
        MpbarSync(10.0F);
    }
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
    {
        if (HasAuthority())
            Multicast_PlaySkill2(Xform);
        else
            Server_PlaySkill2(Xform);
    }
}

void AGreyStone::Skill3()
{
    Skill3coolTime(0.2f);
    AttackDamage += AttackDamageUp;
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
    {
        Niagara->SetVisibility(true);
        GetMesh()->SetOverlayMaterial(Mat);
        MpbarSync(10.0F);
    }
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
    {
        if (HasAuthority())
            Multicast_PlaySkill3();
        else
            Server_PlaySkill3();
    }
}

void AGreyStone::Skill4()
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
        UGameplayStatics::FinishSpawningActor(A4, Xform);
        MpbarSync(10.0F);
    }
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
    {
        if (HasAuthority())
            Multicast_PlaySkill4(Xform);
        else
            Server_PlaySkill4(Xform);
    }
}

AGreyStone::AGreyStone()
{

}
void AGreyStone::Multicast_PlaySkill1_Implementation(FTransform form)
{
    A1 = GetWorld()->SpawnActorDeferred<ASkill1_Actor>(Sk1, form, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A1->SetAttackDamage(Info->Skill1_ATK);
    UGameplayStatics::FinishSpawningActor(A1, form);
}

void AGreyStone::Server_PlaySkill1_Implementation(FTransform form)
{
    Multicast_PlaySkill1(form);
}

void AGreyStone::Multicast_PlaySkill2_Implementation(FTransform form)
{
    A2 = GetWorld()->SpawnActorDeferred<ASkill2_Actor>(Sk2, form, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A2->SetAttackDamage(Info->Skill2_ATK);
    UGameplayStatics::FinishSpawningActor(A2, form);
}

void AGreyStone::Server_PlaySkill2_Implementation(FTransform form)
{
    Multicast_PlaySkill2(form);
}

void AGreyStone::Multicast_PlaySkill3_Implementation()
{
    GetMesh()->SetOverlayMaterial(Mat);
    Niagara->SetVisibility(true);
}

void AGreyStone::Server_PlaySkill3_Implementation()
{
    Multicast_PlaySkill3();
}

void AGreyStone::Multicast_PlaySkill4_Implementation(FTransform form)
{
    A4 = GetWorld()->SpawnActorDeferred<ASkill4_Actor>(Sk4, form, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A4->SetAttackDamage(Info->Skill4_ATK);
    UGameplayStatics::FinishSpawningActor(A4, form);
}

void AGreyStone::Server_PlaySkill4_Implementation(FTransform form)
{
    Multicast_PlaySkill4(form);
}

