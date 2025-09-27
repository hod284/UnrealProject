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
    PlayerController = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
    if (PlayerController)
    {
        if (PlayerController-> HasAuthority())
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
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame|| 
        GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
        SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, pitch);
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
    {
        if (PlayerController && PlayerController->IsLocalController()&&HasAuthority())
        {
            SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, pitch);
        }
        else if (PlayerController&&PlayerController->IsLocalController() && !HasAuthority())
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
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp||
        GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
    {
        if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
            Multicast_PlayASkill(Xform);
        else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
            Server_PlayASkill(Xform);
    }
    Atn += 1;
}

void ADarkMagition::Skill1()
{
    Skill1coolTime(0.5f);
    FVector SpawnLocation = FVector::ZeroVector;
    if (CameraTarget != NULL)
        SpawnLocation = FVector(TargetLocation.X, TargetLocation.Y, 0);
    else
        SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0) + GetActorForwardVector() * 100.0f;
    FRotator SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    FVector  Loc = SpawnLocation;
    FRotator Rot = SpawnRotation;
    FVector  Scl = FVector(1, 1, 1);
    FTransform Xform(Rot, Loc, Scl);
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
    {
        A1 = GetWorld()->SpawnActorDeferred<ASkill1_Magition>(Sk1, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
        A1->SetAttackDamage(Info->Skill1_ATK);
        A1->IngoreActor(this);
        UGameplayStatics::FinishSpawningActor(A1, Xform);
    }
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp||
        GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
    {
        if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
            Multicast_PlaySkill1(Xform);
        else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
            Server_PlaySkill1(Xform);
    }
    MpbarSync(10.0F);
}

void ADarkMagition::Skill2()
{
    Skill2coolTime(0.5f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 120);
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
        A2 = GetWorld()->SpawnActorDeferred<ASkill2_Magition>(Sk2, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
        A2->SetTagetTransform(TargetTransform);
        A2->SetAttackDamage(Info->Skill2_ATK);
        A2->IngoreActor(this);
        UGameplayStatics::FinishSpawningActor(A2, Xform);
    }
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp||
        GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
    {
        if (PlayerController && PlayerController->IsLocalController()&&HasAuthority())
            Multicast_PlaySkill2(Xform, TargetTransform);
        else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
            Server_PlaySkill2(Xform, TargetTransform);
    }
    MpbarSync(10.0F);
}

void ADarkMagition::Skill3()
{
    Skill3coolTime(0.5f);
    FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 80);
    FRotator SpawnRotation = FRotator::ZeroRotator;
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame||
        GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
        SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
    {
        if (PlayerController && PlayerController->IsLocalController()&&HasAuthority())
        {
            SpawnRotation = FRotator(0, GetMesh()->GetRelativeRotation().Yaw, 0);
        }
        else if (PlayerController&&PlayerController->IsLocalController() && !HasAuthority())
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
        A3->IngoreActor(this);
        UGameplayStatics::FinishSpawningActor(A3, Xform);
    }
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp||
        GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
    {
        if (PlayerController && PlayerController->IsLocalController()&&HasAuthority())
            Multicast_PlaySkill3(Xform);
        else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
            Server_PlaySkill3(Xform);
    }
    MpbarSync(10.0F);
}

void ADarkMagition::Skill4()
{
    Skill4coolTime(0.5f);
    FVector SpawnLocation = FVector::ZeroVector;
    if (CameraTarget != NULL)
        SpawnLocation = FVector(TargetLocation.X, TargetLocation.Y, 0);
    else
        SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0) + GetActorForwardVector() * 100.0f;
    FRotator SpawnRotation =  FRotator::ZeroRotator;
    FVector  Loc = SpawnLocation;
    FRotator Rot = SpawnRotation;
    FVector  Scl = FVector(1, 1, 1);
    FTransform Xform(Rot, Loc, Scl);
    if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
    {
        A4 = GetWorld()->SpawnActorDeferred<ASkill4_Magition>(Sk4, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
        A4->SetAttackDamage(Info->Skill4_ATK);
        A4->IngoreActor(this);
        UGameplayStatics::FinishSpawningActor(A4, Xform);
    }
    else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp||
        GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
    {
        if (PlayerController && PlayerController->IsLocalController()&&HasAuthority())
            Multicast_PlaySkill4(Xform);
        else if(PlayerController && PlayerController->IsLocalController() && !HasAuthority())
            Server_PlaySkill4(Xform);
    }
    MpbarSync(10.0F);
}
void ADarkMagition::Multicast_PlayASkill_Implementation(FTransform form)
{
    AS = GetWorld()->SpawnActorDeferred<ASlashAttack_Magition>(Attack, form, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    AS->SetAttackDamage(Info->ATK);
    AS->IngoreActor(this);
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
    A1->IngoreActor(this);
    UGameplayStatics::FinishSpawningActor(A1, form);
}

void ADarkMagition::Server_PlaySkill1_Implementation(FTransform form)
{
    Multicast_PlaySkill1(form);
}

void ADarkMagition::Multicast_PlaySkill2_Implementation(FTransform form, USceneComponent *TargetScene)
{
        A2 = GetWorld()->SpawnActorDeferred<ASkill2_Magition>(Sk2, form, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
        A2->SetTagetTransform(TargetScene);
        A2->SetAttackDamage(Info->Skill2_ATK);
        A2->IngoreActor(this);
        UGameplayStatics::FinishSpawningActor(A2, form);
}

void ADarkMagition::Server_PlaySkill2_Implementation(FTransform form, USceneComponent* TargetScene)
{
    Multicast_PlaySkill2(form, TargetScene);
}

void ADarkMagition::Multicast_PlaySkill3_Implementation(FTransform form)
{
    A3 = GetWorld()->SpawnActorDeferred<ASkill3_Magition>(Sk3, form, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    A3->SetAttackDamage(Info->Skill3_ATK);
    A3->IngoreActor(this);
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
    A4->IngoreActor(this);
    UGameplayStatics::FinishSpawningActor(A4, form);
}

void ADarkMagition::Server_PlaySkill4_Implementation(FTransform form)
{
    Multicast_PlaySkill4(form);
}
