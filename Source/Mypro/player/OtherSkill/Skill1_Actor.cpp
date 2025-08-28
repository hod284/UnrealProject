// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill1_Actor.h"

// Sets default values
ASkill1_Actor::ASkill1_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxColider = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	NiagaraParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE"));
	SetRootComponent(NiagaraParticle);
	BoxColider->SetupAttachment(NiagaraParticle);
	BoxColider->SetCollisionProfileName("PlayerSkill"); 
	BoxColider->OnComponentHit.AddDynamic(this, &ASkill1_Actor::OnHit_Skill);
	// 오버랩 인벤트 활성화
	BoxColider->SetGenerateOverlapEvents(true); // 안전하게 켜두기
	BoxColider->OnComponentBeginOverlap.AddDynamic(this, &ASkill1_Actor::OnCapsuleBeginOverlap_Skill);
	BoxColider->OnComponentEndOverlap.AddDynamic(this, &ASkill1_Actor::OnCapsuleEndOverlap_Skill);
}

// Called when the game starts or when spawned
void ASkill1_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkill1_Actor::OnHit_Skill(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	FString s = OtherActor->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("skill_hit:%s"), *s);
	UE_LOG(LogMypro, Warning, TEXT("ATTACKDAMAGE:%f"), AttAckDamage);

}


void ASkill1_Actor::OnCapsuleBeginOverlap_Skill(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{

	FString s = OtherActor->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("skill_overlap:%s"), *s);
	UE_LOG(LogMypro, Warning, TEXT("ATTACKDAMAGE:%f"), AttAckDamage);
}

void ASkill1_Actor::OnCapsuleEndOverlap_Skill(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	FString s = OtherActor->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("skill_pverlapend:%s"), *s);
	UE_LOG(LogMypro, Warning, TEXT("ATTACKDAMAGE:%f"), AttAckDamage);

}

// Called every frame
void ASkill1_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

