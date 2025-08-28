// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill4_Magition.h"
#include "../../singleton/DataManager.h"
// Sets default values
ASkill4_Magition::ASkill4_Magition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxColider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BOX"));
	NiagaraParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE"));
	SetRootComponent(NiagaraParticle);
	BoxColider->SetupAttachment(NiagaraParticle);
	BoxColider->SetCollisionProfileName("PlayerSkill");
	BoxColider->OnComponentHit.AddDynamic(this, &ASkill4_Magition::OnHit_Skil4_Magition);
	// 오버랩 인벤트 활성화
	BoxColider->SetGenerateOverlapEvents(true); // 안전하게 켜두기
	BoxColider->OnComponentBeginOverlap.AddDynamic(this, &ASkill4_Magition::OnCapsuleBeginOverlap_Skil4_Magition);
	BoxColider->OnComponentEndOverlap.AddDynamic(this, &ASkill4_Magition::OnCapsuleEndOverlap_Skil4_Magition);
}

// Called when the game starts or when spawned
void ASkill4_Magition::BeginPlay()
{
	Super::BeginPlay();
	const FCharacterInfo* Infog = GetWorld()->GetGameInstance()->GetSubsystem<UDataManager>()->GetDatainfo_D();
	AttAckDamage = Infog->Skill4_ATK;
}
void ASkill4_Magition::OnHit_Skil4_Magition(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	FString s = OtherActor->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("skil4_hit:%s"), *s);
	UE_LOG(LogMypro, Warning, TEXT("ATTACKDAMAGE:%f"), AttAckDamage);

}
void ASkill4_Magition::OnCapsuleBeginOverlap_Skil4_Magition(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	FString s = OtherActor->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("skil4_overlap:%s"), *s);
	UE_LOG(LogMypro, Warning, TEXT("ATTACKDAMAGE:%f"), AttAckDamage);

}
void ASkill4_Magition::OnCapsuleEndOverlap_Skil4_Magition(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	FString s = OtherActor->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("skil4_overlap:%s"), *s);
	UE_LOG(LogMypro, Warning, TEXT("ATTACKDAMAGE:%f"), AttAckDamage);

}
// Called every frame
void ASkill4_Magition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

