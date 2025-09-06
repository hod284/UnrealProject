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
	// ������ �κ�Ʈ Ȱ��ȭ
	BoxColider->SetGenerateOverlapEvents(true); // �����ϰ� �ѵα�
	BoxColider->OnComponentBeginOverlap.AddDynamic(this, &ASkill3_Magition::OnCapsuleBeginOverlap_Skil3_Magition);
	BoxColider->OnComponentEndOverlap.AddDynamic(this, &ASkill3_Magition::OnCapsuleEndOverlap_Skil3_Magition);
}

// Called when the game starts or when spawned
void ASkill3_Magition::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().ClearTimer(Time);
	GetWorld()->GetTimerManager().SetTimer(Time, FTimerDelegate::CreateLambda([this]() {
		Destroy();
		}), ActorDestroyTime, false);
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
	FString s = OtherActor->GetName();
	UE_LOG(LogMypro, Warning, TEXT("skil3_hit_m:%s"), *s);

}
void ASkill3_Magition::OnCapsuleBeginOverlap_Skil3_Magition(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	FString s = OtherActor->GetName();
	UE_LOG(LogMypro, Warning, TEXT("skil3_overlap_m:%s"), *s);
	float pe = static_cast<float>(AttackDamage);
	UGameplayStatics::ApplyDamage(OtherActor, pe, GetInstigatorController(), this, UDamageType::StaticClass());
}
void ASkill3_Magition::OnCapsuleEndOverlap_Skil3_Magition(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	FString s = OtherActor->GetName();
	UE_LOG(LogMypro, Warning, TEXT("skil3_overlap_m:%s"), *s);


}
