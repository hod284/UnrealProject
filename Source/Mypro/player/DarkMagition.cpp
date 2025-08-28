// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkMagition.h"

ADarkMagition::ADarkMagition()
{

}

void ADarkMagition::BeginPlay()
{
	Super::BeginPlay();
    Info = GetWorld()->GetGameInstance()->GetSubsystem<UDataManager>()->GetDatainfo_D();
    PlayerHp = Info->HP;
    PlayerMp = Info->MP;
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
    AActor* A = GetWorld()->SpawnActor<AActor>(Attack, SpawnLocation, SpawnRotation);
    ASlashAttack_Magition* S = Cast<ASlashAttack_Magition>(A);
    S->SetAttAckDamage(Info->ATK);
    Atn += 1;
}

void ADarkMagition::Skill1()
{
    Skill1coolTime(0.5f);
    FVector SpawnLocation = FVector(TargetLocation.X, TargetLocation.Y, 0);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    AActor* A = GetWorld()->SpawnActor<AActor>(Sk1, SpawnLocation, SpawnRotation);
    ASkill1_Magition* S = Cast<ASkill1_Magition>(A);
    S->SetAttAckDamage(Info->Skill1_ATK);
}

void ADarkMagition::Skill2()
{
    Skill2coolTime(0.5f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    AActor* A = GetWorld()->SpawnActor<AActor>(Sk2, SpawnLocation, SpawnRotation);
    ASkill2_Magition* S = Cast<ASkill2_Magition>(A);
    S->SetAttAckDamage(Info->Skill2_ATK);
    S->SetTagetLocation(TargetLocation);
}

void ADarkMagition::Skill3()
{
    Skill3coolTime(0.5f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 80);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    AActor* A = GetWorld()->SpawnActor<AActor>(Sk3, SpawnLocation, SpawnRotation);
    ASkill3_Magition* S = Cast<ASkill3_Magition>(A);
    S->SetAttAckDamage(Info->Skill3_ATK);
}

void ADarkMagition::Skill4()
{
    Skill4coolTime(0.5f);
    FVector SpawnLocation = FVector(TargetLocation.X, TargetLocation.Y, 0);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    AActor* A = GetWorld()->SpawnActor<AActor>(Sk4, SpawnLocation, SpawnRotation);
    ASkill4_Magition* S = Cast<ASkill4_Magition>(A);
    S->SetAttAckDamage(Info->Skill4_ATK);
}
