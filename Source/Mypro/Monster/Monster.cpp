// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	MovementComponent = CreateDefaultSubobject<UMonsterPawnMovement>(TEXT("MOVMENT"));
	CapsuleComponent->bVisualizeComponent = true;
	const ConstructorHelpers::FObjectFinder<UBehaviorTree> BTree(TEXT("/Script/AIModule.BehaviorTree'/Game/BT/MonsterTREE.MonsterTREE'"));
    if(BTree.Succeeded())
	    MonsterBehaviorTree = BTree.Object;
	/*
	enum class EAutoPossessAI : uint8
    {
    Disabled,               // AI �ڵ� ��ȯ �� ��
    PlacedInWorld,          // �����Ϳ��� �̸� ��ġ�� Pawn�� AI�� ����
    Spawned,                // ��Ÿ�� �� Spawn�� Pawn�� AI�� ����
    PlacedInWorldOrSpawned  // �� �� �ش� �� �׻� AI ����
    };
	*/
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AMonsterController::StaticClass();
	MovementComponent->SetUpdatedComponent(RootComponent);

	bUseControllerRotationYaw = true; // ��Ʈ�ѷ��� Yaw ȸ���� Pawn�� ����
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	SetGenericTeamId(FGenericTeamId(TeamMonster));
	AnimInstance = Cast<UMonsterAnimInstance>(MeshComponent ->GetAnimInstance());
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController && MonsterBehaviorTree)
	{
		AIController->RunBehaviorTree(MonsterBehaviorTree);
		AIController->GetBlackboardComponent()->SetValueAsFloat("NoramlAttackRange", NoramlAttackRange);
		AIController->GetBlackboardComponent()->SetValueAsFloat("SpecialAttackRange", SpecialAttackRange);
	}
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

