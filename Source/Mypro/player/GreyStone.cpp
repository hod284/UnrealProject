// Fill out your copyright notice in the Description page of Project Settings.


#include "GreyStone.h"

void AGreyStone::NAttack()
{
}
void AGreyStone::BeginPlay()
{
    Super::BeginPlay();
    Info = GetWorld()->GetGameInstance()->GetSubsystem<UDataManager>()->GetDatainfo_G();
    PlayerHp = Info->HP;
    PlayerMp = Info->MP;
    AttackDamage = Info->ATK;
    AttackDamageUp = Info->Skill3_ATK;
}
void AGreyStone::Skill1()
{
    Skill1coolTime(0.5f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    FVector  Loc = SpawnLocation;
    FRotator Rot = SpawnRotation;
    FVector  Scl = FVector(1, 1, 1);
    FTransform Xform(Rot, Loc, Scl);
    ASkill1_Actor* A = GetWorld()->SpawnActorDeferred<ASkill1_Actor>(Sk1, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A->SetAttAckDamage(Info->Skill1_ATK);
    UGameplayStatics::FinishSpawningActor(A, Xform);
}

void AGreyStone::Skill2()
{
    Skill2coolTime(0.4f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    FVector  Loc = SpawnLocation;
    FRotator Rot = SpawnRotation;
    FVector  Scl = FVector(1, 1, 1);
    FTransform Xform(Rot, Loc, Scl);
    ASkill2_Actor* A = GetWorld()->SpawnActorDeferred<ASkill2_Actor>(Sk2, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A->SetAttAckDamage(Info->Skill2_ATK);
    UGameplayStatics::FinishSpawningActor(A, Xform);
}

void AGreyStone::Skill3()
{
    Skill3coolTime(0.2f);
    GetMesh()->SetOverlayMaterial(Mat);
    AttackDamage += AttackDamageUp;
    Niagara->SetVisibility(true);
}

void AGreyStone::Skill4()
{
    Skill4coolTime(0.1f);
    FVector SpawnLocation = FVector(TargetLocation.X, TargetLocation.Y, 0);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    FVector  Loc = SpawnLocation;
    FRotator Rot = SpawnRotation;
    FVector  Scl = FVector(1, 1, 1);
    FTransform Xform(Rot, Loc, Scl);
    ASkill4_Actor* A = GetWorld()->SpawnActorDeferred<ASkill4_Actor>(Sk4, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A->SetAttAckDamage(Info->Skill4_ATK);
    UGameplayStatics::FinishSpawningActor(A, Xform);
}

AGreyStone::AGreyStone()
{

}
