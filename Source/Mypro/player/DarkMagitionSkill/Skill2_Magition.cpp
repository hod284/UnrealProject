// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill2_Magition.h"

// Sets default values
ASkill2_Magition::ASkill2_Magition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxColider = CreateDefaultSubobject<USphereComponent>(TEXT("BOX"));
	NiagaraParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE"));
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("SP"));
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MOVEMENT"));
	SetRootComponent(NiagaraParticle);
	BoxColider->SetupAttachment(NiagaraParticle);
	Spline->SetupAttachment(NiagaraParticle);
	Movement->InitialSpeed = 1000.0f;
	Movement->ProjectileGravityScale = 0.0f;
	Movement->OnProjectileStop.AddDynamic(this,&ASkill2_Magition::ProjectileStop);
	BoxColider->SetCollisionProfileName("PlayerSkill");
}
void ASkill2_Magition::OnHit_Skil2_Magition(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{


}
void ASkill2_Magition::OnCapsuleBeginOverlap_Skil2_Magition(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{


}
void ASkill2_Magition::OnCapsuleEndOverlap_Skil2_Magition(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{


}

// Called when the game starts or when spawned
void ASkill2_Magition::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill2_Magition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ASkill2_Magition::ProjectileStop(const FHitResult& rersult)
{
	

}

