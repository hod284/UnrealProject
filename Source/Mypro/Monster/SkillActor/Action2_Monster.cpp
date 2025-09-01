// Fill out your copyright notice in the Description page of Project Settings.


#include "Action2_Monster.h"

// Sets default values
AAction2_Monster::AAction2_Monster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxColider = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	NiagaraParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE"));
	SetRootComponent(NiagaraParticle);
	BoxColider->SetupAttachment(NiagaraParticle);
	BoxColider->SetCollisionProfileName("Monsterskill");
	BoxColider->OnComponentHit.AddDynamic(this, &AAction2_Monster::OnHit_Action2_M);
	// 오버랩 인벤트 활성화
	BoxColider->SetGenerateOverlapEvents(true); // 안전하게 켜두기
	BoxColider->OnComponentBeginOverlap.AddDynamic(this, &AAction2_Monster::OnCapsuleBeginOverlap_Action2_M);
	BoxColider->OnComponentEndOverlap.AddDynamic(this, &AAction2_Monster::OnCapsuleEndOverlap_Action2_M);
}

// Called when the game starts or when spawned
void AAction2_Monster::BeginPlay()
{
	Super::BeginPlay();
	NiagaraParticle->SetActive(false);
}
void AAction2_Monster::OnHit_Action2_M(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{


}
void AAction2_Monster::OnCapsuleBeginOverlap_Action2_M(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	FString s = OtherActor->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("AC2_overlap:%s"), *s);
	float pe = static_cast<float>(AttackDamage);
	UGameplayStatics::ApplyDamage(OtherActor, pe, GetInstigatorController(), this, UDamageType::StaticClass());

}
void AAction2_Monster::OnCapsuleEndOverlap_Action2_M(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{


}
// Called every frame
void AAction2_Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AAction2_Monster::Init()
{
	NiagaraParticle->SetActive(true);
}
void AAction2_Monster::Reset()
{
	NiagaraParticle->SetActive(false);
}
