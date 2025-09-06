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
    FVector center = GetActorLocation()+CurrentVelocity * 50;
    bool Collision = GetWorld()->SweepMultiByChannel(result, center, center,
        FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2,
        FCollisionShape::MakeCapsule(Radious,200), param);
    DrawDebugCapsule(GetWorld(), center, 200, Radious, FQuat::Identity, FColor::Green, false, 2.f);
    //DrawDebugAltCone
    float pe = static_cast<float>(AttackDamage);
    if (Collision)
    {
        float	Origin = FMath::Cos(FMath::DegreesToRadians(45.f));

        for (auto& Hit : result)
        {
            if (Hit.GetActor()->IsA<APawn>())
                AddMpbar(10);
            UGameplayStatics::ApplyDamage(Hit.GetActor(), pe, GetInstigatorController(), this, UDamageType::StaticClass());
        }
    }
}

void AAurora::Skill1()
{
    Skill1coolTime(0.5f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    FVector  Loc = SpawnLocation;
    FRotator Rot = SpawnRotation;
    FVector  Scl = FVector(1, 1, 1);
    FTransform Xform(Rot, Loc, Scl);
    ASkill1_Actor* A = GetWorld()->SpawnActorDeferred<ASkill1_Actor>(Sk1, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A->SetAttackDamage(Info->Skill1_ATK);
    UGameplayStatics::FinishSpawningActor(A, Xform);
    MpbarSync(10.0F);
}

void AAurora::Skill2()
{
    Skill2coolTime(0.4f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    FVector  Loc = SpawnLocation;
    FRotator Rot = SpawnRotation;
    FVector  Scl = FVector(1, 1, 1);
    FTransform Xform(Rot, Loc, Scl);
    ASkill2_Actor* A = GetWorld()->SpawnActorDeferred<ASkill2_Actor>(Sk2, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A->SetAttackDamage(Info->Skill2_ATK);
    UGameplayStatics::FinishSpawningActor(A, Xform);
    MpbarSync(10.0F);
}

void AAurora::Skill3()
{
     Skill3coolTime(0.2f);
     GetMesh()->SetOverlayMaterial(Mat);
     AttackDamage += AttackDamageUp;
     Niagara->SetVisibility(true);
     MpbarSync(10.0F);
}

void AAurora::Skill4()
{
    Skill4coolTime(0.1f);
    FVector SpawnLocation = FVector(TargetLocation.X, TargetLocation.Y, 0);
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    FVector  Loc = SpawnLocation;
    FRotator Rot = SpawnRotation;
    FVector  Scl = FVector(1, 1, 1);
    FTransform Xform(Rot, Loc, Scl);
    ASkill4_Actor* A = GetWorld()->SpawnActorDeferred<ASkill4_Actor>(Sk4, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A->SetAttackDamage(Info->Skill4_ATK);
    UGameplayStatics::FinishSpawningActor(A, Xform);
    MpbarSync(10.0F);
}
