// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionMonster.h"

// Sets default values
AMinionMonster::AMinionMonster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	MovementComponent = CreateDefaultSubobject<UMonsterPawnMovement>(TEXT("MOVMENT"));
	Damagesh = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageWidget"));
	const ConstructorHelpers::FObjectFinder<UBehaviorTree> BTree(TEXT("/Script/AIModule.BehaviorTree'/Game/BT/MinionTree.MinionTree'"));
	if (BTree.Succeeded())
		MonsterBehaviorTree = BTree.Object;
	static ConstructorHelpers::FClassFinder<UMonsterHPBar>UI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/widget/MonsterHpbarWidget.MonsterHpbarWidget_C'"));
	if (UI.Succeeded())
		Damagesh->SetWidgetClass(UI.Class);
	Damagesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Damagesh->SetWidgetSpace(EWidgetSpace::Screen);
	Damagesh->SetDrawSize(FVector2D(200, 80));
	Damagesh->SetAbsolute(false, false, false);
	Damagesh->SetupAttachment(RootComponent);
	CapsuleComponent->SetCollisionProfileName("Monster");
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AMinionController::StaticClass();
	MovementComponent->SetUpdatedComponent(RootComponent);
	bUseControllerRotationYaw = true; 
	SetReplicates(true);
	SetReplicateMovement(true);
}
// Called when the game starts or when spawned
void AMinionMonster::BeginPlay()
{
	Super::BeginPlay();
	UMySingleton* GI = Cast<UMySingleton>(UGameplayStatics::GetGameInstance(GetWorld()));
	Info = GI->GetDatainfo_Minion();
	MonsterHpConst =MonsterHp = static_cast <float>(Info->HP);
	HP = 1.0f;
	AnimInstance = Cast<UMonsterAnimInstance>(MeshComponent->GetAnimInstance());
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController && MonsterBehaviorTree)
	{
		AIController->RunBehaviorTree(MonsterBehaviorTree);
		AIController->GetBlackboardComponent()->SetValueAsFloat("NoramlAttackRange", NoramlAttackRange);
	}
	FVector  Loc = FVector::ZeroVector;
	FRotator Rot = FRotator::ZeroRotator;
	FVector  Scl = FVector(1, 1, 1);
	FTransform Xform(Rot, Loc, Scl);
	Ac3 = GetWorld()->SpawnActorDeferred<AAction3_Monster>(Sk3, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	Ac3->SetAttackDamage(Info->Skill1_ATK);
	UGameplayStatics::FinishSpawningActor(Ac3, Xform);
}

// Called every frame
void  AMinionMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

} 

// Called to bind functionality to input
void  AMinionMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}
void AMinionMonster::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMinionMonster, HP);
}
void AMinionMonster::OnRep_Health()
{
	UMonsterHPBar* hp = Cast<UMonsterHPBar>(Damagesh->GetWidget());
	hp->SetHpBar(HP);
}

void AMinionMonster::AttackSuper()
{
}
void AMinionMonster::AttackShooting()
{
}
float AMinionMonster::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	MonsterHp -= DamageAmount;
	float HpTemp = (MonsterHp/ MonsterHpConst) * 100;
	HP = HpTemp / 100.0F;
	if (HasAuthority()) // 서버에서만 변경
	{
		OnRep_Health(); // 서버에서도 즉시 UI 반영
	}
	return DamageAmount;
}

