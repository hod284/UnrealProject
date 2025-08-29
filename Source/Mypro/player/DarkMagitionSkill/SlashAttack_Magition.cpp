// Fill out your copyright notice in the Description page of Project Settings.



#include "SlashAttack_Magition.h"
// Sets default values
ASlashAttack_Magition::ASlashAttack_Magition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxColider = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	NiagaraParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE"));
	SetRootComponent(NiagaraParticle);
	BoxColider->SetupAttachment(NiagaraParticle);
	BoxColider->SetCollisionProfileName("PlayerSkill");
	BoxColider->OnComponentHit.AddDynamic(this, &ASlashAttack_Magition::OnHit_Slash_Magition);
	// 오버랩 인벤트 활성화
	BoxColider->SetGenerateOverlapEvents(true); // 안전하게 켜두기
	BoxColider->OnComponentBeginOverlap.AddDynamic(this, &ASlashAttack_Magition::OnCapsuleBeginOverlap_Slash_Magition);
	BoxColider->OnComponentEndOverlap.AddDynamic(this, &ASlashAttack_Magition::OnCapsuleEndOverlap_Slash_Magition);
}

// Called when the game starts or when spawned
void ASlashAttack_Magition::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().ClearTimer(Time);
	GetWorld()->GetTimerManager().SetTimer(Time, FTimerDelegate::CreateLambda([this]() {
		Destroy();
		}), 3.0, false);
}

// Called every frame
void ASlashAttack_Magition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASlashAttack_Magition::OnHit_Slash_Magition(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{


}
void ASlashAttack_Magition::OnCapsuleBeginOverlap_Slash_Magition(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{


}
void ASlashAttack_Magition::OnCapsuleEndOverlap_Slash_Magition(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{


}