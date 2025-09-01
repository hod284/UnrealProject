// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill2_Magition.h"
// Sets default values
ASkill2_Magition::ASkill2_Magition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxColider = CreateDefaultSubobject<USphereComponent>(TEXT("BOX"));
	NiagaraParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE"));
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MOVEMENT"));
	SetRootComponent(BoxColider);
	BoxColider->SetMobility(EComponentMobility::Movable);
	BoxColider->SetSimulatePhysics(false);
	NiagaraParticle->SetupAttachment(BoxColider);
	Movement->SetUpdatedComponent(BoxColider);
	Movement->InitialSpeed = TravelSpeed;
	Movement->MaxSpeed = TravelSpeed;
	Movement->ProjectileGravityScale = 0.f;
	Movement->bRotationFollowsVelocity = true;// 현재속가 향하는 방향으로 자동 회전
	Movement->bAutoActivate = true;// 무브 컴포넌트 켤지여부
	Movement->bForceSubStepping = true; // 고속/저FPS 안정
	Movement ->ProjectileGravityScale = 0.f;
	Movement->OnProjectileStop.AddDynamic(this,&ASkill2_Magition::ProjectileStop);
	BoxColider->SetCollisionProfileName("PlayerObject");
}
void ASkill2_Magition::OnHit_Skil2_Magition(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	FString s = OtherActor->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("skill2_hit:%s"), *s);


}
void ASkill2_Magition::OnCapsuleBeginOverlap_Skil2_Magition(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	FString s = OtherActor->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("skil2_overlap:%s"), *s);


}
void ASkill2_Magition::OnCapsuleEndOverlap_Skil2_Magition(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	FString s = OtherActor->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("skil2_overlap:%s"), *s);


}

// Called when the game starts or when spawned
void ASkill2_Magition::BeginPlay()
{
	Super::BeginPlay();
	// 호밍은 언리얼에서 만드는 유도 탄 을 만들 때 사용하는것으로 타겟컴포넌트를 대입해 타겟을 설정한다
	Movement->bIsHomingProjectile = true;
	Movement->HomingTargetComponent = UScene;
	Movement->HomingAccelerationMagnitude = StartAccel;
	ApplyInitialSideKick(); // ← 여기서 "확 티나는 곡선"의 시작 방향을 준다
}

// Called every frame
void ASkill2_Magition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateAccel(DeltaTime);
}
void ASkill2_Magition::ProjectileStop(const FHitResult& rersult)
{
	Destroy();
	FString s = rersult.GetActor()->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("skil2_Stop :%s"), *s);
	float pe = static_cast<float>(AttackDamage);
	UGameplayStatics::ApplyDamage(rersult.GetActor(), pe, GetInstigatorController(), this, UDamageType::StaticClass());
}

void ASkill2_Magition::ApplyInitialSideKick()
{
	// 타겟이 있으면 그쪽을 기준으로 옆 방향을 계산해 살짝 틀어 쏜다.
	FVector dir = GetActorForwardVector(); // 기본
	if (UScene)
	{
		const FVector toTarget = (UScene->GetComponentLocation() - GetActorLocation()).GetSafeNormal();
		// 옆 방향(right): Up × Forward (위 기준 롤링 없이 시계 반대쪽)
		const FVector right = FVector::CrossProduct(FVector::UpVector, toTarget).GetSafeNormal();

		const float rad = FMath::DegreesToRadians(45);
		const FVector curvy = (toTarget * FMath::Cos(rad) + right * FMath::Sin(rad)).GetSafeNormal();
		dir = curvy;
	}

	Movement->Velocity = dir * TravelSpeed;
}

void ASkill2_Magition::UpdateAccel(float dt)
{
	// KINDA_SMALL_NUMBER :부동 소수점을 방지하기 위해 0.0을 비교하기 위한 언리얼 메크로
	if (AccelRampTime <= KINDA_SMALL_NUMBER)
	{
		Movement->HomingAccelerationMagnitude = 8000.0f; 
		return; 
	}

	Elapsed += dt;
	const float alpha = FMath::Clamp(Elapsed / AccelRampTime, 0.f, 1.f);
	// 가속 램프업(부드럽게): S-curve
	const float smooth = alpha * alpha * (3.f - 2.f * alpha);
	Movement->HomingAccelerationMagnitude = FMath::Lerp(StartAccel, EndAccel, smooth);

	// 막판 보정(선택): 충분히 가까우면 급히 붙이기
	if (UScene)
	{
		const float d = FVector::Dist(GetActorLocation(), UScene->GetComponentLocation());
		if (d < 600.f) // 6m 남으면 강제 가속 업
		{
			Movement->HomingAccelerationMagnitude = FMath::Max(Movement->HomingAccelerationMagnitude, EndAccel * 1.5f);
		}
	}
}