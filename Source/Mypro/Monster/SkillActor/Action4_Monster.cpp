// Fill out your copyright notice in the Description page of Project Settings.


#include "Action4_Monster.h"
// Sets default values
AAction4_Monster::AAction4_Monster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Transform = CreateDefaultSubobject<USceneComponent>(TEXT("tr"));
	BoxColider1 = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BOX1"));
	NiagaraParticle1 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE1"));
	BoxColider2 = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BOX2"));
	NiagaraParticle2 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE2"));
	BoxColider3 = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BOX3"));
	NiagaraParticle3 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE3"));
	BoxColider4 = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BOX4"));
	NiagaraParticle4 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE4"));
	SetRootComponent(Transform);
	NiagaraParticle1->SetupAttachment(Transform);
	NiagaraParticle2->SetupAttachment(Transform);
	NiagaraParticle3->SetupAttachment(Transform);
	NiagaraParticle4->SetupAttachment(Transform);
	BoxColider1->SetupAttachment(NiagaraParticle1);
	BoxColider1->SetCollisionProfileName("Monsterskill");
	BoxColider2->SetupAttachment(NiagaraParticle2);
	BoxColider2->SetCollisionProfileName("Monsterskill");
	BoxColider3->SetupAttachment(NiagaraParticle3);
	BoxColider3->SetCollisionProfileName("Monsterskill");
	BoxColider4->SetupAttachment(NiagaraParticle4);
	BoxColider4->SetCollisionProfileName("Monsterskill");
	BoxColider1->OnComponentHit.AddDynamic(this, &AAction4_Monster::OnHit_Action4_M);
	// 오버랩 인벤트 활성화
	BoxColider1->SetGenerateOverlapEvents(true); // 안전하게 켜두기
	BoxColider1->OnComponentBeginOverlap.AddDynamic(this, &AAction4_Monster::OnCapsuleBeginOverlap_Action4_M);
	BoxColider1->OnComponentEndOverlap.AddDynamic(this, &AAction4_Monster::OnCapsuleEndOverlap_Action4_M);
	BoxColider2->OnComponentHit.AddDynamic(this, &AAction4_Monster::OnHit_Action4_M);
	// 오버랩 인벤트 활성화
	BoxColider2->SetGenerateOverlapEvents(true); // 안전하게 켜두기
	BoxColider2->OnComponentBeginOverlap.AddDynamic(this, &AAction4_Monster::OnCapsuleBeginOverlap_Action4_M);
	BoxColider2->OnComponentEndOverlap.AddDynamic(this, &AAction4_Monster::OnCapsuleEndOverlap_Action4_M);
	BoxColider3->OnComponentHit.AddDynamic(this, &AAction4_Monster::OnHit_Action4_M);
	// 오버랩 인벤트 활성화
	BoxColider3->SetGenerateOverlapEvents(true); // 안전하게 켜두기
	BoxColider3->OnComponentBeginOverlap.AddDynamic(this, &AAction4_Monster::OnCapsuleBeginOverlap_Action4_M);
	BoxColider3->OnComponentEndOverlap.AddDynamic(this, &AAction4_Monster::OnCapsuleEndOverlap_Action4_M);
	BoxColider4->OnComponentHit.AddDynamic(this, &AAction4_Monster::OnHit_Action4_M);
	// 오버랩 인벤트 활성화
	BoxColider4->SetGenerateOverlapEvents(true); // 안전하게 켜두기
	BoxColider4->OnComponentBeginOverlap.AddDynamic(this, &AAction4_Monster::OnCapsuleBeginOverlap_Action4_M);
	BoxColider4->OnComponentEndOverlap.AddDynamic(this, &AAction4_Monster::OnCapsuleEndOverlap_Action4_M);
}

// Called when the game starts or when spawned
void AAction4_Monster::BeginPlay()
{
	Super::BeginPlay();	
	NiagaraParticle1->SetActive(false);
	NiagaraParticle2->SetActive(false);
	NiagaraParticle3->SetActive(false);
	NiagaraParticle4->SetActive(false);
	BoxColider1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxColider2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxColider3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxColider4->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
void AAction4_Monster::OnHit_Action4_M(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{


}
void AAction4_Monster::OnCapsuleBeginOverlap_Action4_M(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	FString s = OtherActor->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("AC4_overlap:%s"), *s);
	float pe = static_cast<float>(AttackDamage);
	UGameplayStatics::ApplyDamage(OtherActor, pe, GetInstigatorController(), this, UDamageType::StaticClass());
	BoxColider1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxColider2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxColider3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxColider4->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
void AAction4_Monster::OnCapsuleEndOverlap_Action4_M(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{


}
// Called every frame
void AAction4_Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAction4_Monster::Init()
{
	NiagaraParticle1->SetActive(true);
	NiagaraParticle2->SetActive(true);
	NiagaraParticle3->SetActive(true);
	NiagaraParticle4->SetActive(true);
	BoxColider1->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxColider2->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxColider3->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxColider4->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
void AAction4_Monster::Reset()
{
	NiagaraParticle1->SetActive(false);
	NiagaraParticle2->SetActive(false);
	NiagaraParticle3->SetActive(false);
	NiagaraParticle4->SetActive(false);
	BoxColider1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxColider2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxColider3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxColider4->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

