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
    GetWorld()->SpawnActor<AActor>(Sk1, SpawnLocation, SpawnRotation);
}

void AGreyStone::Skill2()
{
    Skill2coolTime(0.4f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    GetWorld()->SpawnActor<AActor>(Sk2, SpawnLocation, SpawnRotation);
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
    GetWorld()->SpawnActor<AActor>(Sk4, SpawnLocation, SpawnRotation);
}

AGreyStone::AGreyStone()
{

}
