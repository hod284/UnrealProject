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
	CapsuleComponent->bVisualizeComponent = true;
	const ConstructorHelpers::FObjectFinder<UBehaviorTree> BTree(TEXT("/Script/AIModule.BehaviorTree'/Game/BT/MonsterTREE.MonsterTREE'"));
    if(BTree.Succeeded())
	    MonsterBehaviorTree = BTree.Object;
	CapsuleComponent->SetCollisionProfileName("Monster");
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	/*
	enum class EAutoPossessAI : uint8
    {
    Disabled,               // AI 자동 소환 안 함
    PlacedInWorld,          // 에디터에서 미리 배치된 Pawn만 AI를 붙임
    Spawned,                // 런타임 중 Spawn된 Pawn만 AI를 붙임
    PlacedInWorldOrSpawned  // 둘 다 해당 → 항상 AI 붙임
    };
	*/
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AMonsterController::StaticClass();
	MovementComponent->SetUpdatedComponent(RootComponent);
	SetGenericTeamId(FGenericTeamId(TeamMonster));
	bUseControllerRotationYaw = true; // 컨트롤러의 Yaw 회전을 Pawn에 적용
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	Info = GetWorld()->GetGameInstance()->GetSubsystem<UDataManager>()->GetDatainfo_Monster();
	MonsterHp = Info->HP;
	MonsterStun = Info->StunGage;
	AnimInstance = Cast<UMonsterAnimInstance>(MeshComponent ->GetAnimInstance());
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController && MonsterBehaviorTree)
	{
		AIController->RunBehaviorTree(MonsterBehaviorTree);
		AIController->GetBlackboardComponent()->SetValueAsFloat("NoramlAttackRange", NoramlAttackRange);
	}
	Brain = AIController->BrainComponent;
	if (Brain )
		Brain->PauseLogic(TEXT("ManualStop")); // 브레인 정지
}

void AMonster::Start()
{
	if (Brain)
		Brain->ResumeLogic(TEXT("ManualStopdf")); // 브레인 정지
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
	AAction1_Monster* A = GetWorld()->SpawnActorDeferred<AAction1_Monster>(Sk1, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	A->SetAttAckDamage(Info->Skill1_ATK);
	UGameplayStatics::FinishSpawningActor(A, Xform);
}

void AMonster::Attack2()
{
	FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
	FVector  Loc = SpawnLocation;
	FRotator Rot = GetActorRotation();
	FVector  Scl = FVector(1, 1, 1);
	FTransform Xform(Rot, Loc, Scl);
	AAction2_Monster* A = GetWorld()->SpawnActorDeferred<AAction2_Monster>(Sk2, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	A->SetAttAckDamage(Info->Skill2_ATK);
	UGameplayStatics::FinishSpawningActor(A, Xform);
}

void AMonster::Attack3()
{
	FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 90);
	FVector  Loc = SpawnLocation;
	FRotator Rot = GetActorRotation();
	FVector  Scl = FVector(1, 1, 1);
	FTransform Xform(Rot, Loc, Scl);
	AAction3_Monster* A = GetWorld()->SpawnActorDeferred<AAction3_Monster>(Sk3, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	A->SetAttAckDamage(Info->Skill3_ATK);
	UGameplayStatics::FinishSpawningActor(A, Xform);
}

void AMonster::Attack4()
{
	FVector SpawnLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
	FVector  Loc = SpawnLocation;
	FRotator Rot = GetActorRotation();
	FVector  Scl = FVector(1, 1, 1);
	FTransform Xform(Rot, Loc, Scl);
	AAction4_Monster* A = GetWorld()->SpawnActorDeferred<AAction4_Monster>(Sk4, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	A->SetAttAckDamage(Info->Skill4_ATK);
	UGameplayStatics::FinishSpawningActor(A, Xform);
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
	return 0;
}

