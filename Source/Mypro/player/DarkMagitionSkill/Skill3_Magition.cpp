// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill3_Magition.h"

// Sets default values
ASkill3_Magition::ASkill3_Magition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxColider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BOX"));
	NiagaraParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE"));
	SetRootComponent(NiagaraParticle);
	BoxColider->SetupAttachment(NiagaraParticle);
	BoxColider->SetCollisionProfileName("PlayerSkill");
	BoxColider->OnComponentHit.AddDynamic(this, &ASkill3_Magition::OnHit_Skil3_Magition);
	// 오버랩 인벤트 활성화
	BoxColider->SetGenerateOverlapEvents(true); // 안전하게 켜두기
	BoxColider->OnComponentBeginOverlap.AddDynamic(this, &ASkill3_Magition::OnCapsuleBeginOverlap_Skil3_Magition);
	BoxColider->OnComponentEndOverlap.AddDynamic(this, &ASkill3_Magition::OnCapsuleEndOverlap_Skil3_Magition);
}

// Called when the game starts or when spawned
void ASkill3_Magition::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill3_Magition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ASkill3_Magition::OnHit_Skil3_Magition(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	FString s = OtherActor->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("skil3_hit:%s"), *s);
	UE_LOG(LogMypro, Warning, TEXT("ATTACKDAMAGE:%f"), AttAckDamage);

}
void ASkill3_Magition::OnCapsuleBeginOverlap_Skil3_Magition(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	FString s = OtherActor->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("skil3_overlap:%s"), *s);
	UE_LOG(LogMypro, Warning, TEXT("ATTACKDAMAGE:%f"), AttAckDamage);

}
void ASkill3_Magition::OnCapsuleEndOverlap_Skil3_Magition(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	FString s = OtherActor->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("skil3_overlap:%s"), *s);
	UE_LOG(LogMypro, Warning, TEXT("ATTACKDAMAGE:%f"), AttAckDamage);

}
