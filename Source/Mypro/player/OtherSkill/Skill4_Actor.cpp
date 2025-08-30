// Fill out your copyright notice in the Description page of Project Settings.

#include "Skill4_Actor.h"

// Sets default values
ASkill4_Actor::ASkill4_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxColider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BOX"));
	NiagaraParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE"));
	SetRootComponent(NiagaraParticle);
	BoxColider->SetupAttachment(NiagaraParticle);
	BoxColider->SetCollisionProfileName("PlayerSkill");
	BoxColider->OnComponentHit.AddDynamic(this, &ASkill4_Actor::OnHit_Skil4);
	// 오버랩 인벤트 활성화
	BoxColider->SetGenerateOverlapEvents(true); // 안전하게 켜두기
	BoxColider->OnComponentBeginOverlap.AddDynamic(this, &ASkill4_Actor::OnCapsuleBeginOverlap_Skil4);
	BoxColider->OnComponentEndOverlap.AddDynamic(this, &ASkill4_Actor::OnCapsuleEndOverlap_Skil4);
}

// Called when the game starts or when spawned
void ASkill4_Actor::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().ClearTimer(Time);
	GetWorld()->GetTimerManager().SetTimer(Time, FTimerDelegate::CreateLambda([this]() {
		Destroy();
		}), 2.0f,false);
}
void ASkill4_Actor::OnHit_Skil4(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{

	FString s = OtherActor->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("skil4_hit:%s"), *s);

}


void ASkill4_Actor::OnCapsuleBeginOverlap_Skil4(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{

	FString s = OtherActor->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("skil4_overlap:%s"), *s);

}

void ASkill4_Actor::OnCapsuleEndOverlap_Skil4(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	FString s = OtherActor->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("skil4_pverlapend:%s"), *s);


}
// Called every frame
void ASkill4_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

