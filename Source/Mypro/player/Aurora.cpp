 // Fill out your copyright notice in the Description page of Project Settings.


#include "Aurora.h"

AAurora::AAurora()
{

}

void AAurora::BeginPlay()
{
    Super::BeginPlay();
  Info =  GetWorld()->GetGameInstance()->GetSubsystem<UDataManager>()->GetDatainfo_W();
  PlayerHp = Info->HP;
  PlayerMp = Info->MP;
  AttackDamage = Info->ATK;
  AttackDamageUp = Info->Skill3_ATK;
}
void AAurora::NAttack()
{
}

void AAurora::Skill1()
{
    Skill1coolTime(0.5f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    AActor *A =  GetWorld()->SpawnActor<AActor>(Sk1,SpawnLocation,SpawnRotation);
    ASkill1_Actor* S = Cast<ASkill1_Actor>(A);
    S->SetAttAckDamage(Info->Skill1_ATK);
}

void AAurora::Skill2()
{
    Skill2coolTime(0.4f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    AActor* A = GetWorld()->SpawnActor<AActor>(Sk2, SpawnLocation, SpawnRotation);
    ASkill1_Actor* S = Cast<ASkill1_Actor>(A);
    S->SetAttAckDamage(Info->Skill2_ATK);
}

void AAurora::Skill3()
{
     Skill3coolTime(0.2f);
     GetMesh()->SetOverlayMaterial(Mat);
     AttackDamage += AttackDamageUp;
     Niagara->SetVisibility(true);
}

void AAurora::Skill4()
{
    Skill4coolTime(0.1f);
    FVector SpawnLocation = FVector(TargetLocation.X, TargetLocation.Y, 0);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    AActor* A = GetWorld()->SpawnActor<AActor>(Sk4, SpawnLocation, SpawnRotation);
    ASkill1_Actor* S = Cast<ASkill1_Actor>(A);
    S->SetAttAckDamage(Info->Skill4_ATK);
}
