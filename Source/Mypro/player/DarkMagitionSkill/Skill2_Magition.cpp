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
	Movement->bRotationFollowsVelocity = true;// ����Ӱ� ���ϴ� �������� �ڵ� ȸ��
	Movement->bAutoActivate = true;// ���� ������Ʈ ��������
	Movement->bForceSubStepping = true; // ���/��FPS ����
	Movement ->ProjectileGravityScale = 0.f;
	Movement->OnProjectileStop.AddDynamic(this,&ASkill2_Magition::ProjectileStop);
	BoxColider->SetCollisionProfileName("PlayerObject");
}
void ASkill2_Magition::OnHit_Skil2_Magition(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	FString s = OtherActor->GetName();
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
	FString s = OtherActor->GetName();
	UE_LOG(LogMypro, Warning, TEXT("skil2_overlap:%s"), *s);


}
void ASkill2_Magition::OnCapsuleEndOverlap_Skil2_Magition(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	FString s = OtherActor->GetName();
	UE_LOG(LogMypro, Warning, TEXT("skil2_overlap:%s"), *s);


}

// Called when the game starts or when spawned
void ASkill2_Magition::BeginPlay()
{
	Super::BeginPlay();
	// ȣ���� �𸮾󿡼� ����� ���� ź �� ���� �� ����ϴ°����� Ÿ��������Ʈ�� ������ Ÿ���� �����Ѵ�
	Movement->bIsHomingProjectile = true;
	Movement->HomingTargetComponent = UScene;
	Movement->HomingAccelerationMagnitude = StartAccel;
	ApplyInitialSideKick(); // �� ���⼭ "Ȯ Ƽ���� �"�� ���� ������ �ش�
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
	FString s = rersult.GetActor()->GetName();
	UE_LOG(LogMypro, Warning, TEXT("skil2_Stop :%s"), *s);
	float pe = static_cast<float>(AttackDamage);
	UGameplayStatics::ApplyDamage(rersult.GetActor(), pe, GetInstigatorController(), this, UDamageType::StaticClass());

}

void ASkill2_Magition::ApplyInitialSideKick()
{
	FVector dir = GetActorForwardVector();
	if (UScene)
	{
		const FVector toTarget = (UScene->GetComponentLocation() - GetActorLocation()).GetSafeNormal();

		const FVector right = FVector::CrossProduct(FVector::UpVector, toTarget).GetSafeNormal();

		const float rad = FMath::DegreesToRadians(45);
		const FVector curvy = (toTarget * FMath::Cos(rad) + right * FMath::Sin(rad)).GetSafeNormal();
		dir = curvy;
	}

	Movement->Velocity = dir * TravelSpeed;
}

void ASkill2_Magition::UpdateAccel(float dt)
{
	if (AccelRampTime <= KINDA_SMALL_NUMBER)
	{
		Movement->HomingAccelerationMagnitude = 8000.0f; 
		return; 
	}

	Elapsed += dt;
	const float alpha = FMath::Clamp(Elapsed / AccelRampTime, 0.f, 1.f);
	const float smooth = alpha * alpha * (3.f - 2.f * alpha);
	Movement->HomingAccelerationMagnitude = FMath::Lerp(StartAccel, EndAccel, smooth);

	if (UScene)
	{
		const float d = FVector::Dist(GetActorLocation(), UScene->GetComponentLocation());
		if (d < 600.f) 
		{
			Movement->HomingAccelerationMagnitude = FMath::Max(Movement->HomingAccelerationMagnitude, EndAccel * 1.5f);
		}
	}
}