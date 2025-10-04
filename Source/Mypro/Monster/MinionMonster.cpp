// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionMonster.h"
#include "../common/PartyRoomController.h"
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
	StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSource"));
	const ConstructorHelpers::FObjectFinder<UBehaviorTree> BTree(TEXT("/Script/AIModule.BehaviorTree'/Game/BT/MinionTree.MinionTree'"));
	if (BTree.Succeeded())
		MonsterBehaviorTree = BTree.Object;
	static ConstructorHelpers::FClassFinder<UMonsterHPBar>DamageUI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/widget/MonsterHpbarWidget.MonsterHpbarWidget_C'"));
	if (DamageUI.Succeeded())
		Damagesh->SetWidgetClass(DamageUI.Class);
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
	Attack1 = static_cast <float>(Info->Skill1_ATK);
	AnimInstance = Cast<UMonsterAnimInstance>(MeshComponent->GetAnimInstance());
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController && MonsterBehaviorTree)
	{
		AIController->RunBehaviorTree(MonsterBehaviorTree);
		AIController->GetBlackboardComponent()->SetValueAsFloat("NoramlAttackRange", NoramlAttackRange);
	}
	if(HasAuthority())
	Brain = AIController->BrainComponent;
	FVector  Loc = FVector::ZeroVector;
	FRotator Rot = FRotator::ZeroRotator;
	FVector  Scl = FVector(1, 1, 1);
	FTransform Xform(Rot, Loc, Scl);
	Ac3 = GetWorld()->SpawnActorDeferred<AAction3_Monster>(Sk3, Xform, this, GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	Ac3->SetAttackDamage(Attack1);
	UGameplayStatics::FinishSpawningActor(Ac3, Xform);
	if (StimuliSource)
	{
		StimuliSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimuliSource->RegisterForSense(TSubclassOf<UAISense_Hearing>());
		StimuliSource->RegisterWithPerceptionSystem();
		StimuliSource->SetAutoActivate(true);
	}
	UI = Cast<UPartyRoomWidgetClass>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetPartyRoom_widget());
}

// Called every frame
void  AMinionMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (MonsterHp <= KINDA_SMALL_NUMBER)
	{
		if (Brain && Brain->IsRunning())
			Brain->StopLogic(TEXT("DIE"));
		if (Ac3)
			Ac3->Destroy();
		Death_M();
	}
	if (UI&&UI->GetLose() && Brain && Brain->IsRunning())
		Brain->StopLogic(TEXT("DIE"));
} 

// Called to bind functionality to input
void  AMinionMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}
void AMinionMonster::AttackSuper()
{
	TArray<FHitResult>	result;
	FCollisionQueryParams	param;
	param.AddIgnoredActor(this);
	param.bTraceComplex = false;
	float Radious = 100.0f;
	FVector center = GetActorLocation() + GetActorForwardVector() * 150;
	bool Collision;
	ECollisionChannel channel = ECollisionChannel::ECC_GameTraceChannel6; 
	Collision = GetWorld()->SweepMultiByChannel(result, center, center,
		FQuat::Identity, channel,
		FCollisionShape::MakeCapsule(Radious, 200), param);
	//DrawDebugCapsule(GetWorld(), center, 200, Radious, FQuat::Identity, FColor::Green, false, 2.f);
	if (Collision)
	{
		for (auto& Hit : result)
		{
			if (Hit.GetActor()->IsA<APawn>())
			{
				 UGameplayStatics::ApplyDamage(Hit.GetActor(), Attack1, GetInstigatorController(), this, UDamageType::StaticClass());
			}
		}
	}
}
void AMinionMonster::AttackShooting()
{
	FVector LO1 = MeshComponent->GetSocketLocation("Muzzle_Front");
	FVector SpawnLocation = LO1;
	AActor* a3 = Cast<AActor>(Ac3);
	a3->SetActorLocation(SpawnLocation);
	a3->SetActorRotation(FRotator(0,GetActorRotation().Yaw,0));
	if(Ac3)
	Ac3->Init();
}
void AMinionMonster::AttackShootingEnd()
{
	if (Ac3)
	Ac3->ResetAction();
}
void AMinionMonster::MinionDeath()
{
	if (HasAuthority())
	{
		APartyRoomController* party = Cast<APartyRoomController>(UGameplayStatics::GetActorOfClass(GetWorld(), APartyRoomController::StaticClass()));
		party->MinusMaxium();
		Destroy();
	}
}
float AMinionMonster::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	MeshComponent->SetOverlayMaterial(Overlap);
	GetWorld()->GetTimerManager().ClearTimer(Timer);
	GetWorld()->GetTimerManager().SetTimer(Timer, [this]() {
		MeshComponent->SetOverlayMaterial(nullptr);
		}, 0.3, false);
	MonsterHp -= DamageAmount;
	float HpTemp = (MonsterHp/ MonsterHpConst) * 100;
	HP = HpTemp / 100.0F;
	if (HasAuthority()) // 서버에서만 변경
		Multicast_Sethp(HP);
	else
		Server_Sethp(HP);
	return DamageAmount;
}

void AMinionMonster::Multicast_PlayAttack_Implementation(EMonsterDefaultAnim type)
{
	MonSterAnim = type;
}
void AMinionMonster::Multicast_Run_Implementation(EMonsterDefaultAnim type)
{
	MonSterAnim = type;
}
void AMinionMonster::Multicast_Death_Implementation(EMonsterDefaultAnim type)
{
	MonSterAnim = type;
}
void AMinionMonster::Multicast_idle_Implementation(EMonsterDefaultAnim type)
{
	MonSterAnim = type;
}
void AMinionMonster::Idle_M()
{
	if (HasAuthority())
		Multicast_idle(EMonsterDefaultAnim ::Idle);
	else
		Server_idle(EMonsterDefaultAnim::Idle);
}
void AMinionMonster::Attack_M()
{
	if (HasAuthority())
		Multicast_PlayAttack(EMonsterDefaultAnim::Attack1);
	else
		Server_PlayAttack(EMonsterDefaultAnim::Attack1);
}
void AMinionMonster::Death_M()
{
	if (HasAuthority())
		Multicast_Death(EMonsterDefaultAnim::Death);
	else
		Server_Death(EMonsterDefaultAnim::Death);
}
void AMinionMonster::Run_M()
{
	if (HasAuthority())
		Multicast_Run(EMonsterDefaultAnim::Run);
	else
		Server_Run(EMonsterDefaultAnim::Run);
}

void AMinionMonster::Server_PlayAttack_Implementation(EMonsterDefaultAnim type)
{
	Multicast_PlayAttack(type);
}

void AMinionMonster::Server_Run_Implementation(EMonsterDefaultAnim type)
{
	Multicast_Run(type);
}

void AMinionMonster::Server_Death_Implementation(EMonsterDefaultAnim type)
{
	Multicast_Death(type);
}

void AMinionMonster::Server_idle_Implementation(EMonsterDefaultAnim type)
{
	Multicast_idle(type);
}

void AMinionMonster::Multicast_Sethp_Implementation(float hp)
{
	UMonsterHPBar* hpbar = Cast<UMonsterHPBar>(Damagesh->GetWidget());
	hpbar->SetHpBar(hp);
}

void AMinionMonster::Server_Sethp_Implementation(float hp)
{
	Multicast_Sethp(hp);
}
