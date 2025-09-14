// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkMagition.h"

ADarkMagition::ADarkMagition()
{

}

void ADarkMagition::BeginPlay()
{
	Super::BeginPlay();
    UMySingleton* GI = Cast<UMySingleton>(UGameplayStatics::GetGameInstance(GetWorld()));
    Info = GI->GetDatainfo_D();
    PlayerHp = static_cast<float>(Info->HP);
    PlayerMp = static_cast<float>(Info->MP);
    PlayerHp_Const = PlayerHp;
    PlayerMp_Const = PlayerMp;
    AttackDamage = 0;
    AttackDamageUp = 0;
}

void ADarkMagition::NAttack()
{
    if (Atn > 2)
        Atn = 0;
    float pitch = 0;
    switch (Atn)
    {
    case 0:
        pitch = 30;
        break;
    case 1:
        pitch = 60;
        break;
    case 2:
        pitch =300;
        break;
    }
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 90);
    FRotator SpawnRotation = FRotator::ZeroRotator;
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
        SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, pitch);
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
    {
        if (HasAuthority())
        {
            SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, pitch);
        }
        else if (PlayerController&&PlayerController->IsLocalController())
        {
            SpawnRotation = FRotator(0, (GetMesh()->GetRelativeRotation().Yaw - GetActorRotation().Yaw) - 90, pitch);
        }
    }
    FRotator SpawnRotationShowing = SpawnRotation;
    FVector  Loc = SpawnLocation;
    FRotator Rot = SpawnRotationShowing;
    FVector  Scl = FVector(1, 1, 1);
    FTransform Xform(Rot, Loc, Scl);
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
    {
        AS = GetWorld()->SpawnActorDeferred<ASlashAttack_Magition>(Attack, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
        AS->SetAttackDamage(Info->ATK);
        UGameplayStatics::FinishSpawningActor(AS, Xform);
        if (AS->SomeHit)
            AddMpbar(10);
    }
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
    {
        if (HasAuthority())
            Multicast_PlayASkill(Xform);
        else
            Server_PlayASkill(Xform);
    }
    Atn += 1;
}

void ADarkMagition::Skill1()
{
    Skill1coolTime(0.5f);
    FVector SpawnLocation = FVector(TargetLocation.X, TargetLocation.Y, 0);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    FVector  Loc = SpawnLocation;
    FRotator Rot = SpawnRotation;
    FVector  Scl = FVector(1, 1, 1);
    FTransform Xform(Rot, Loc, Scl);
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
    {
        A1 = GetWorld()->SpawnActorDeferred<ASkill1_Magition>(Sk1, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
        A1->SetAttackDamage(Info->Skill1_ATK);
        UGameplayStatics::FinishSpawningActor(A1, Xform);
        MpbarSync(10.0F);
    }
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
    {
        if (HasAuthority())
            Multicast_PlaySkill1(Xform);
        else
            Server_PlaySkill1(Xform);
    }
}

void ADarkMagition::Skill2()
{
    Skill2coolTime(0.5f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 120);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    FVector  Loc = SpawnLocation;
    FRotator Rot = SpawnRotation;
    FVector  Scl = FVector(1, 1, 1);
    FTransform Xform(Rot, Loc, Scl);
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
    {
        A2 = GetWorld()->SpawnActorDeferred<ASkill2_Magition>(Sk2, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
        A2->SetTagetTransform(TargetTransform);
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

void ADarkMagition::Skill3()
{
    Skill3coolTime(0.5f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 80);
    FRotator SpawnRotation = FRotator::ZeroRotator;
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
        SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
    {
        if (HasAuthority())
        {
            SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
        }
        else if (PlayerController&&PlayerController->IsLocalController())
        {
            SpawnRotation = FRotator(0, (GetMesh()->GetRelativeRotation().Yaw - GetActorRotation().Yaw) - 90,0);
        }
    }
    FRotator SpawnRotationShowing = SpawnRotation;
    FVector  Loc = SpawnLocation;
    FRotator Rot = SpawnRotationShowing;
    FVector  Scl = FVector(1, 1, 1);
    FTransform Xform(Rot, Loc, Scl);
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
    {
        A3 = GetWorld()->SpawnActorDeferred<ASkill3_Magition>(Sk3, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
        A3->SetAttackDamage(Info->Skill3_ATK);
        UGameplayStatics::FinishSpawningActor(A3, Xform);
        MpbarSync(10.0F);
    }
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
    {
        if (HasAuthority())
            Multicast_PlaySkill3(Xform);
        else
            Server_PlaySkill3(Xform);
    }
}

void ADarkMagition::Skill4()
{
    Skill4coolTime(0.5f);
    FVector SpawnLocation = FVector(TargetLocation.X, TargetLocation.Y, 0);
    FRotator SpawnRotation =  FRotator::ZeroRotator;
    FVector  Loc = SpawnLocation;
    FRotator Rot = SpawnRotation;
    FVector  Scl = FVector(1, 1, 1);
    FTransform Xform(Rot, Loc, Scl);
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
    {
        A4 = GetWorld()->SpawnActorDeferred<ASkill4_Magition>(Sk4, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
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
void ADarkMagition::Multicast_PlayASkill_Implementation(FTransform form)
{
    AS = GetWorld()->SpawnActorDeferred<ASlashAttack_Magition>(Attack, form, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    AS->SetAttackDamage(Info->ATK);
    UGameplayStatics::FinishSpawningActor(AS, form);
}

void ADarkMagition::Server_PlayASkill_Implementation(FTransform form)
{
    Multicast_PlayASkill(form);
}

void ADarkMagition::Multicast_PlaySkill1_Implementation(FTransform form)
{
    A1 = GetWorld()->SpawnActorDeferred<ASkill1_Magition>(Sk1, form, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A1->SetAttackDamage(Info->Skill1_ATK);
    UGameplayStatics::FinishSpawningActor(A1, form);
}

void ADarkMagition::Server_PlaySkill1_Implementation(FTransform form)
{
    Multicast_PlaySkill1(form);
}

void ADarkMagition::Multicast_PlaySkill2_Implementation(FTransform form)
{
    A2 = GetWorld()->SpawnActorDeferred<ASkill2_Magition>(Sk2, form, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A2->SetTagetTransform(TargetTransform);
    A2->SetAttackDamage(Info->Skill2_ATK);
    UGameplayStatics::FinishSpawningActor(A2, form);
}

void ADarkMagition::Server_PlaySkill2_Implementation(FTransform form)
{
    Multicast_PlaySkill2(form);
}

void ADarkMagition::Multicast_PlaySkill3_Implementation(FTransform form)
{
    A3 = GetWorld()->SpawnActorDeferred<ASkill3_Magition>(Sk3, form, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A3->SetAttackDamage(Info->Skill3_ATK);
    UGameplayStatics::FinishSpawningActor(A3, form);
}

void ADarkMagition::Server_PlaySkill3_Implementation(FTransform form)
{
    Multicast_PlaySkill3(form);
}

void ADarkMagition::Multicast_PlaySkill4_Implementation(FTransform form)
{
    A4 = GetWorld()->SpawnActorDeferred<ASkill4_Magition>(Sk4, form, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A4->SetAttackDamage(Info->Skill4_ATK);
    UGameplayStatics::FinishSpawningActor(A4, form);
}

void ADarkMagition::Server_PlaySkill4_Implementation(FTransform form)
{
    Multicast_PlaySkill4(form);
}
