 // Fill out your copyright notice in the Description page of Project Settings.


#include "Aurora.h"

AAurora::AAurora()
{

}

void AAurora::NAttack()
{
}

void AAurora::Skill1()
{
    Skill1coolTime(0.5f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    GetWorld()->SpawnActor<AActor>(Sk1,SpawnLocation,SpawnRotation);
}

void AAurora::Skill2()
{
    Skill2coolTime(0.4f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    GetWorld()->SpawnActor<AActor>(Sk2, SpawnLocation, SpawnRotation);
}

void AAurora::Skill3()
{
     Skill3coolTime(0.2f);
}

void AAurora::Skill4()
{
    Skill4coolTime(0.1f);
    FVector SpawnLocation = FVector(TargetLocation.X, TargetLocation.Y, 0);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    GetWorld()->SpawnActor<AActor>(Sk4, SpawnLocation, SpawnRotation);
}
