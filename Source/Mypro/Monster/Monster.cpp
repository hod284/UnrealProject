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
	SetGenericTeamId(FGenericTeamId(TeamMonster));
	bUseControllerRotationYaw = true; // ��Ʈ�ѷ��� Yaw ȸ���� Pawn�� ����
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	UMySingleton* GI = Cast<UMySingleton>(UGameplayStatics::GetGameInstance(GetWorld()));
	Info = GI->GetDatainfo_Monster();
	MonsterHp = static_cast <float>(Info->HP);
	MonsterStun = static_cast <float>(Info->StunGage);
	HP = 1.0f;
	Stun = 1.0f;
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
	Ac2->SetAttackDamage(Info->Skill2_ATK);
	UGameplayStatics::FinishSpawningActor(Ac2, Xform);
	VI = Cast<AActor>(Ac2);
	Ac3 = GetWorld()->SpawnActorDeferred<AAction3_Monster>(Sk3, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	Ac3->SetAttackDamage(Info->Skill3_ATK);
	UGameplayStatics::FinishSpawningActor(Ac3, Xform);
	VI = Cast<AActor>(Ac3);
	Ac4 = GetWorld()->SpawnActorDeferred<AAction4_Monster>(Sk4, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	Ac4->SetAttackDamage(Info->Skill4_ATK);
	UGameplayStatics::FinishSpawningActor(Ac4, Xform);
	VI = Cast<AActor>(Ac4);
	UI = Cast<UPlayMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetPlayMainUI_widget());
}

void AMonster::Start()
{
	if (Brain)
		Brain->ResumeLogic(TEXT("ManualStopdf")); // �극�� ����
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
	Ac1->SetAttackDamage(Info->Skill1_ATK);
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
	FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 90);
	FRotator SpawnRotation = FRotator(90, -GetActorRotation().Yaw, 0);
	AActor* VI = Cast<AActor>(Ac3);
	VI->SetActorLocationAndRotation(SpawnLocation, SpawnRotation);
	Ac3->Init();
	UE_LOG(LogMypro, Warning, TEXT("at3"));
}

void AMonster::Attack4()
{
	FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y,-10);
	AActor* VI = Cast<AActor>(Ac4);
	VI->SetActorLocationAndRotation(SpawnLocation, FRotator::ZeroRotator);
	Ac4->Init();
	UE_LOG(LogMypro, Warning, TEXT("at4"));
}

void AMonster::SetMonsterStun(float st)
{
	float conststun = static_cast<float>(Info->StunGage);
	MonsterStun = st;
	UE_LOG(LogMypro, Warning, TEXT("mst:%f"), MonsterStun);
	float StunTemp = (MonsterStun / conststun) * 100;
	UE_LOG(LogMypro, Warning, TEXT("mst:%f"), StunTemp);
	Stun = StunTemp / 100;
	UE_LOG(LogMypro, Warning, TEXT("mst:%f"), Stun);
	if (MonsterStun > conststun)
	{
		MonsterStun = conststun;
		Stun = 1.0f;
	}
	UI->OnStunDamage.Broadcast(Stun);
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	GetWorld()->GetTimerManager().ClearTimer(Timmer);
	GetWorld()->GetTimerManager().SetTimer(Timmer, [this]() {
		MeshComponent->SetOverlayMaterial(nullptr);
		}, 0.3, false);
	if (CanStun)
	{
		MonsterStun -= DamageAmount;
		UE_LOG(LogMypro, Warning, TEXT("mst:%f"), MonsterStun);
		float StunTemp  =(MonsterStun/ static_cast<float>(Info->StunGage)) * 100;
		UE_LOG(LogMypro, Warning, TEXT("mst:%f"), StunTemp);
		Stun = StunTemp/100;
		UE_LOG(LogMypro, Warning, TEXT("mst:%f"),Stun);
		UI ->OnStunDamage.Broadcast(Stun);
	}
	else 
	{
		MonsterHp -= DamageAmount;
		UE_LOG(LogMypro, Warning, TEXT("mhp:%f"), MonsterHp);
		float hptemp = (MonsterHp  /static_cast<float>(Info->HP)) * 100;
		UE_LOG(LogMypro, Warning, TEXT("mhp:%f"), hptemp);
		HP =hptemp/100.0f;
		UE_LOG(LogMypro, Warning, TEXT("mhp:%f"), HP);
		UI->OnDamage_M.Broadcast(HP);
	}
	if (MonsterStun <= KINDA_SMALL_NUMBER)
		CanStun = false;
	if (MonsterHp <= KINDA_SMALL_NUMBER)
	{
		AnimInstance->DeathAni();
		if (Brain)
			Brain->PauseLogic(TEXT("Death")); 
		FVector SpawnLocation(0, 0, 100);
		FRotator SpawnRotation(0, 0, 0);

		AStaticMeshActor* MeshActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), SpawnLocation, SpawnRotation);
		MeshActor ->Rename(TEXT("Portal1"));
		if (MeshActor)
		{
			MeshActor->SetMobility(EComponentMobility::Movable);
			UMySingleton* GI = Cast<UMySingleton>(UGameplayStatics::GetGameInstance(GetWorld()));
			const FItmeTexturAndMeshInfo* Texture = GI->GetTextureInfo();
			UStaticMesh* Mesh = Texture->MeshMap["Portal"];
			MeshActor->GetStaticMeshComponent()->SetStaticMesh(Mesh);
			MeshActor->SetActorScale3D(FVector(1.0f)); 
			CapsuleComponent->SetCollisionProfileName("PlayerSkill");
		}
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		GetWorld()->SpawnActor<AActor>(Portal, FVector(0, -200, 10), FRotator::ZeroRotator, param);
		FVector LO1 = MeshComponent->GetSocketLocation("Melee_Impact_R");
		FVector LO2 = MeshComponent->GetSocketLocation("Impact");
		FVector LO3 = MeshComponent->GetSocketLocation("Melee_Impact_L");
		UNiagaraSystem* Niagara1 = LoadObject<UNiagaraSystem>(GetWorld(), TEXT("/Script/Niagara.NiagaraSystem'/Game/Pack_Simple_Particle_Burst/01_Niagara_Systems/NS_Simple_Burst_Level_3.NS_Simple_Burst_Level_3'"));

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara1, LO1);
		UNiagaraSystem* Niagara2 = LoadObject<UNiagaraSystem>(GetWorld(), TEXT("/Script/Niagara.NiagaraSystem'/Game/Pack_Simple_Particle_Burst/01_Niagara_Systems/NS_Simple_Burst_Level_3.NS_Simple_Burst_Level_3'"));

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara2, LO2);
		UNiagaraSystem* Niagara3 = LoadObject<UNiagaraSystem>(GetWorld(), TEXT("/Script/Niagara.NiagaraSystem'/Game/Pack_Simple_Particle_Burst/01_Niagara_Systems/NS_Simple_Burst_Level_3.NS_Simple_Burst_Level_3'"));

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara3, LO3);
		Death = true;
	}

	return DamageAmount;
}

