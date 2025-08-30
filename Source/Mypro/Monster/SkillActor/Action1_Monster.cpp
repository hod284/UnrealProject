// Fill out your copyright notice in the Description page of Project Settings.


#include "Action1_Monster.h"

// Sets default values
AAction1_Monster::AAction1_Monster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NiagaraParticle_mark= CreateDefaultSubobject<UNiagaraComponent>(TEXT("gr"));
	NiagaraParticle= CreateDefaultSubobject<UNiagaraComponent>(TEXT("ni"));
    BoxColider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("box"));
	SetRootComponent(NiagaraParticle_mark);
	NiagaraParticle->SetupAttachment(NiagaraParticle_mark);
	BoxColider->SetupAttachment(NiagaraParticle_mark);
	BoxColider->SetCollisionProfileName("Monsterskill");
	BoxColider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	NiagaraParticle->SetActive(false);
	BoxColider->OnComponentHit.AddDynamic(this, &AAction1_Monster::OnHit_Action1_M);
	// 오버랩 인벤트 활성화
	BoxColider->SetGenerateOverlapEvents(true); // 안전하게 켜두기
	BoxColider->OnComponentBeginOverlap.AddDynamic(this, &AAction1_Monster::OnCapsuleBeginOverlap_Action1_M);
	BoxColider->OnComponentEndOverlap.AddDynamic(this, &AAction1_Monster::OnCapsuleEndOverlap_Action1_M);
}

// Called when the game starts or when spawned
void AAction1_Monster::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().ClearTimer(Time);
	GetWorld()->GetTimerManager().SetTimer(Time, this,&AAction1_Monster::ShowingtheColider, 0.7, false);
	
}
void AAction1_Monster::OnHit_Action1_M(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{


}
void AAction1_Monster::OnCapsuleBeginOverlap_Action1_M(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{


}
void AAction1_Monster::OnCapsuleEndOverlap_Action1_M(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{


}
// Called every frame
void AAction1_Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// Called every frame
void AAction1_Monster::ShowingtheColider()
{
	BoxColider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	NiagaraParticle->SetActive(true);
	GetWorldTimerManager().ClearTimer(Time);
	GetWorld()->GetTimerManager().SetTimer(Time, FTimerDelegate::CreateLambda([this]() {
		Destroy();
		}), ActorDestroyTime, false);
}

