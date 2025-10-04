// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	MovementComponent = CreateDefaultSubobject<UMonsterPawnMovement>(TEXT("MOVMENT"));
	const ConstructorHelpers::FObjectFinder<UBehaviorTree> BTree(TEXT("/Script/AIModule.BehaviorTree'/Game/BT/MonsterTREE.MonsterTREE'"));
    if(BTree.Succeeded())
	    MonsterBehaviorTree = BTree.Object;
	CapsuleComponent->SetCollisionProfileName("Monster");
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AMonsterController::StaticClass();
	MovementComponent->SetUpdatedComponent(RootComponent);
	bUseControllerRotationYaw = true; 
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	UMySingleton* GI = Cast<UMySingleton>(UGameplayStatics::GetGameInstance(GetWorld()));
	const FItmeTexturAndMeshInfo* Texture = GI->GetTextureInfo();
	textureMap = Texture->textureMap;
	MeshMap =Texture->MeshMap;
	const FCMonsterInfo* Info = GI->GetDatainfo_Monster();
	MonsterHp_Const = MonsterHp = static_cast <float>(Info->HP);
	MonsterStun_Const  =MonsterStun = static_cast <float>(Info->StunGage);
	HP = 1.0f;
	Stun = 1.0f;
	Attak4 = static_cast <float>(Info->Skill4_ATK);
	Attak1= static_cast <float>(Info->Skill1_ATK);
	Attak2= static_cast <float>(Info->Skill2_ATK);
	AnimInstance = Cast<UMonsterAnimInstance>(MeshComponent ->GetAnimInstance());
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController && MonsterBehaviorTree)
	{
		AIController->RunBehaviorTree(MonsterBehaviorTree);
		AIController->GetBlackboardComponent()->SetValueAsFloat("NoramlAttackRange", NoramlAttackRange);
	}
	Brain = AIController->BrainComponent;
	if (Brain )
		Brain->PauseLogic(TEXT("ManualStop")); 
	FVector  Loc = FVector::ZeroVector;
	FRotator Rot = FRotator::ZeroRotator;
	FVector  Scl = FVector(1, 1, 1);
	FTransform Xform(Rot, Loc, Scl);
	AActor* VI = Cast<AActor>(Ac1);
	Ac2 = GetWorld()->SpawnActorDeferred<AAction2_Monster>(Sk2, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	Ac2->SetAttackDamage(Attak2);
	UGameplayStatics::FinishSpawningActor(Ac2, Xform);
	VI = Cast<AActor>(Ac2);
	Ac4 = GetWorld()->SpawnActorDeferred<AAction4_Monster>(Sk4, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	Ac4->SetAttackDamage(Attak4);
	UGameplayStatics::FinishSpawningActor(Ac4, Xform);
	VI = Cast<AActor>(Ac4);
	UI = Cast<UPlayMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetPlayMainUI_widget());
}

void AMonster::Start()
{
	if (Brain)
		Brain->ResumeLogic(TEXT("ManualStopd")); 
}
void AMonster::Attack1()
{
	AMonsterController* controller = Cast<AMonsterController>(GetController());
	FVector lo = controller->GetTarget()->GetActorLocation();
	FVector SpawnLocation = FVector(lo.X, lo.Y, 0);
	FVector  Loc = SpawnLocation;
	FRotator Rot = FRotator::ZeroRotator;
	FVector  Scl = FVector(1, 1, 1);
	FTransform Xform(Rot, Loc, Scl);
	Ac1 = GetWorld()->SpawnActorDeferred<AAction1_Monster>(Sk1, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	Ac1->SetAttackDamage(Attak1);
	UGameplayStatics::FinishSpawningActor(Ac1, Xform);
	UE_LOG(LogMypro, Warning, TEXT("at1"));
}
void AMonster::Attack2()
{
	FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
	AActor* VI = Cast<AActor>(Ac2);
	VI->SetActorLocationAndRotation(SpawnLocation, GetActorRotation());
	Ac2->Init();
	UE_LOG(LogMypro, Warning, TEXT("at2"));
}

void AMonster::Attack3()
{
}

void AMonster::Attack4()
{
	FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y,-10);
	AActor* VI = Cast<AActor>(Ac4);
	VI->SetActorLocationAndRotation(SpawnLocation, FRotator::ZeroRotator);
	Ac4->Init();
	UE_LOG(LogMypro, Warning, TEXT("at4"));
}
void AMonster::MonsterDeath()
{
	if (!itemon)
	{
		FVector SpawnLocation(0, 0, 100);
		FRotator SpawnRotation(0, 0, 0);
		FVector Scale(1.0, 1.0, 1.0);
		FTransform xtransform(SpawnRotation, SpawnLocation, Scale);
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		Params.Name = TEXT("Portal1");                 
		Params.Owner = this;
		MeshActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), xtransform,Params);
		if (MeshActor)
		{
			MeshActor->SetMobility(EComponentMobility::Movable);
			UStaticMesh* Mesh = MeshMap[TEXT("Portal")];
			MeshActor->GetStaticMeshComponent()->SetStaticMesh(Mesh);
		}
		itemon = true;
	}
}
void AMonster::AttackallReset()
{
	if (Ac2)
		Ac2->ResetAction();
	if (Ac4)
		Ac4->ResetAction();
	if (AnimInstance)
	AnimInstance->IdleAni();
}

void AMonster::SetMonsterStun(float st)
{
	MonsterStun = st;
	UE_LOG(LogMypro, Warning, TEXT("mst:%f"), MonsterStun);
	float StunTemp = (MonsterStun / MonsterStun_Const) * 100.0f;
	UE_LOG(LogMypro, Warning, TEXT("mst:%f"), StunTemp);
	Stun = StunTemp / 100.0f;
	UE_LOG(LogMypro, Warning, TEXT("mst:%f"), Stun);
	if (MonsterStun > MonsterStun_Const)
	{
		MonsterStun = MonsterStun_Const;
		Stun = 1.0f;
	}
	UI->OnStunDamage.Broadcast(Stun);
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (MonsterStun <= KINDA_SMALL_NUMBER)
	{
		CanStun = false;
	}
	if (MonsterHp <= KINDA_SMALL_NUMBER)
	{
		Nohp = true;
		if (Brain&&Brain->IsRunning())
			Brain->StopLogic(TEXT("DIE"));
		if (Ac2 )
			Ac2->ResetAction();
		if (Ac4)
			Ac4->ResetAction();
		if (AnimInstance&&AnimInstance ->GetAnimType() != EMonsterDefaultAnim::Death)
		AnimInstance->DeathAni();
	}
	if(UI&&UI->GetPlayerLose()&& Brain && Brain->IsRunning())
		Brain->StopLogic(TEXT("DIE"));
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}
float AMonster::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	MeshComponent->SetOverlayMaterial(Overlap);
	GetWorld()->GetTimerManager().ClearTimer(Timer);
	GetWorld()->GetTimerManager().SetTimer(Timer, [this]() {
		MeshComponent->SetOverlayMaterial(nullptr);
		}, 0.3, false);
	if (CanStun)
	{
		MonsterStun -= DamageAmount;
		UE_LOG(LogMypro, Warning, TEXT("mst:%f"), MonsterStun);
		float StunTemp  =(MonsterStun/ MonsterStun_Const) * 100.0f;
		UE_LOG(LogMypro, Warning, TEXT("mst:%f"), StunTemp);
		Stun = StunTemp/100.0f;
		UE_LOG(LogMypro, Warning, TEXT("mst:%f"),Stun);
		UI ->OnStunDamage.Broadcast(Stun);
	}
	else 
	{
		MonsterHp -= DamageAmount;
		UE_LOG(LogMypro, Warning, TEXT("mhp:%f"), MonsterHp);
		float hptemp = (MonsterHp  / MonsterHp_Const) * 100.0f;
		UE_LOG(LogMypro, Warning, TEXT("mhp:%f"), hptemp);
		HP =hptemp/100.0f;
		UE_LOG(LogMypro, Warning, TEXT("mhp:%f"), HP);
		UI->OnDamage_M.Broadcast(HP);
	}
	return DamageAmount;
}

