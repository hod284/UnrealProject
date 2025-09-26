// Fill out your copyright notice in the Description page of Project Settings.


#include "GreyStone.h"

void AGreyStone::NAttack()
{
    ECollisionChannel channel = ECollisionChannel::ECC_GameTraceChannel2;
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
    {
        channel = ECollisionChannel::ECC_GameTraceChannel2;
        AttackWeapon(CurrentVelocity, channel);
    }
    else  if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
    {
        channel = ECollisionChannel::ECC_GameTraceChannel3;
        if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
            Multicast_NAttack(CurrentVelocity, channel);
        else  if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
            Server_NAttack(CurrentVelocity, channel);
    }
    else if ( GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
    {
        channel = ECollisionChannel::ECC_GameTraceChannel2;
        if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
            Multicast_NAttack(CurrentVelocity, channel);
        else  if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
            Server_NAttack(CurrentVelocity, channel);
    }
}
void AGreyStone::BeginPlay()
{
    Super::BeginPlay();
    UMySingleton* GI = Cast<UMySingleton>(UGameplayStatics::GetGameInstance(GetWorld()));
    Info = GI->GetDatainfo_G();
    PlayerHp = static_cast<float>(Info->HP);
    PlayerMp = static_cast<float>(Info->MP);
    PlayerController = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
    if (PlayerController)
    {
        if (PlayerController->HasAuthority())
        {
            AMyPlayerState* ps = Cast<AMyPlayerState>(PlayerController->PlayerState);
            ps->PlayerHPtotal_H = PlayerHp;
            ps->PlayerHPtotalconst_H = PlayerHp;
        }
        else
        {
            PlayerController->Server_SendthetotalHP(PlayerHp);
        }
    }
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
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame||
        GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
        SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    else  if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
    {
        if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
        {
            SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
        }
        else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
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
        A1->IngoreActor(this);
        UGameplayStatics::FinishSpawningActor(A1, Xform);
    }
    else if(GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp
        || GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
    {
        if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
            Multicast_PlaySkill1(Xform);
        else  if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
            Server_PlaySkill1(Xform);
    }
    MpbarSync(10.0F);
}

void AGreyStone::Skill2()
{
    Skill2coolTime(0.4f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
    FRotator SpawnRotation = FRotator::ZeroRotator;
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame||
        GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
        SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
    {
        if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
        {
            SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
        }
        else  if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
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
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp
        || GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
    {
        if (PlayerController && PlayerController->IsLocalController() &&HasAuthority())
            Multicast_PlaySkill2(Xform);
        else  if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
            Server_PlaySkill2(Xform);
    }
    MpbarSync(10.0F);
}

void AGreyStone::Skill3()
{
    Skill3coolTime(0.2f);
    AttackDamage += AttackDamageUp;
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
    {
        Niagara->SetVisibility(true);
        GetMesh()->SetOverlayMaterial(Mat);
    }
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp||
        GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
    {
        if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
            Multicast_PlaySkill3();
        else   if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
            Server_PlaySkill3();
    }
    MpbarSync(10.0F);
}

void AGreyStone::Skill4()
{
    Skill4coolTime(0.1f);
    FVector SpawnLocation = FVector::ZeroVector;
    if (CameraTarget != NULL)
        SpawnLocation = FVector(TargetLocation.X, TargetLocation.Y, 0);
    else
        SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0) + GetActorForwardVector() * 100.0f;
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
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp||
        GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
    {
        if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
            Multicast_PlaySkill4(Xform);
        else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
            Server_PlaySkill4(Xform);
    }
    MpbarSync(10.0F);
}

AGreyStone::AGreyStone()
{

}
void AGreyStone::Multicast_PlaySkill1_Implementation(FTransform form)
{
    A1 = GetWorld()->SpawnActorDeferred<ASkill1_Actor>(Sk1, form, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A1->SetAttackDamage(Info->Skill1_ATK);
    A1->IngoreActor(this);
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
    A2->IngoreActor(this);
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
    A4->IngoreActor(this);
    UGameplayStatics::FinishSpawningActor(A4, form);
}

void AGreyStone::Server_PlaySkill4_Implementation(FTransform form)
{
    Multicast_PlaySkill4(form);
}

void AGreyStone::Server_NAttack_Implementation(FVector velocity, ECollisionChannel atchannel)
{
    Multicast_NAttack(velocity, atchannel);
}

void AGreyStone::Multicast_NAttack_Implementation(FVector velocity, ECollisionChannel atchannel)
{
    AttackWeapon(velocity, atchannel);
}

void AGreyStone::AttackWeapon(FVector velocity, ECollisionChannel atchannel)
{
    TArray<FHitResult>	result;
    FCollisionQueryParams	param;
    param.AddIgnoredActor(this);
    param.bTraceComplex = false;
    float Radious = 100.0f;
    FVector center = GetActorLocation() + velocity * 100;
    bool Collision;
    ECollisionChannel channel = atchannel;
    Collision = GetWorld()->SweepMultiByChannel(result, center, center,
        FQuat::Identity, channel,
        FCollisionShape::MakeCapsule(Radious, 200), param);
    DrawDebugCapsule(GetWorld(), center, 200, Radious, FQuat::Identity, FColor::Green, false, 2.f);
    float pe = static_cast<float>(AttackDamage);
    if (Collision)
    {
        float	Origin = 45.0f;
        for (auto& Hit : result)
        {
            if (Hit.GetActor()->IsA<APawn>())
            {
                FVector DIr = (GetActorLocation() - Hit.GetActor()->GetActorLocation()).GetSafeNormal();
                FVector Forward = (GetActorLocation() - center).GetSafeNormal();
                float dot = FVector::DotProduct(Forward, DIr);
                float Angle = FMath::RadiansToDegrees(FMath::Acos(dot));
                UE_LOG(LogMypro, Warning, TEXT("Angle : %f"), Angle);
                UE_LOG(LogMypro, Warning, TEXT("origin : %f"), Origin);
                if (Angle <= Origin)
                {
                    AddMpbar(10);
                    UGameplayStatics::ApplyDamage(Hit.GetActor(), pe, GetInstigatorController(), this, UDamageType::StaticClass());
                }
            }
        }
    }
}