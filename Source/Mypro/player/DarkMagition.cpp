// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkMagition.h"

ADarkMagition::ADarkMagition()
{

}

void ADarkMagition::BeginPlay()
{
	Super::BeginPlay();
    Info = GetWorld()->GetGameInstance()->GetSubsystem<UDataManager>()->GetDatainfo_D();
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
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw,pitch);
    FVector  Loc = SpawnLocation;
    FRotator Rot = SpawnRotation;
    FVector  Scl = FVector(1, 1, 1);
    FTransform Xform(Rot, Loc, Scl);
    ASlashAttack_Magition* A = GetWorld()->SpawnActorDeferred<ASlashAttack_Magition>(Attack, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A->SetAttackDamage(Info->ATK);
    UGameplayStatics::FinishSpawningActor(A, Xform);
    if(A ->SomeHit)
    AddMpbar(10);
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
    ASkill1_Magition* A = GetWorld()->SpawnActorDeferred<ASkill1_Magition>(Sk1, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A->SetAttackDamage(Info->Skill1_ATK);
    UGameplayStatics::FinishSpawningActor(A, Xform);
    MpbarSync(10.0F);
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
    ASkill2_Magition* A = GetWorld()->SpawnActorDeferred<ASkill2_Magition>(Sk2, Xform, this,GetInstigator(),ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A->SetTagetTransform(TargetTransform);
    A->SetAttackDamage(Info->Skill2_ATK);
    UGameplayStatics::FinishSpawningActor(A, Xform);
    MpbarSync(10.0F);
}

void ADarkMagition::Skill3()
{
    Skill3coolTime(0.5f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 80);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    FVector  Loc = SpawnLocation;
    FRotator Rot = SpawnRotation;
    FVector  Scl = FVector(1, 1, 1);
    FTransform Xform(Rot, Loc, Scl);
    ASkill3_Magition* A = GetWorld()->SpawnActorDeferred<ASkill3_Magition>(Sk3, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A->SetAttackDamage(Info->Skill3_ATK);
    UGameplayStatics::FinishSpawningActor(A, Xform);
    MpbarSync(10.0F);
}

void ADarkMagition::Skill4()
{
    Skill4coolTime(0.5f);
    FVector SpawnLocation = FVector(TargetLocation.X, TargetLocation.Y, 0);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    FVector  Loc = SpawnLocation;
    FRotator Rot = SpawnRotation;
    FVector  Scl = FVector(1, 1, 1);
    FTransform Xform(Rot, Loc, Scl);
    ASkill4_Magition* A = GetWorld()->SpawnActorDeferred<ASkill4_Magition>(Sk4, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A->SetAttackDamage(Info->Skill4_ATK);
    UGameplayStatics::FinishSpawningActor(A, Xform);
    MpbarSync(10.0F);
}
