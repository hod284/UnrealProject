// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill2_Actor.h"
#include "../../singleton/DataManager.h"
#include "../../singleton/GameManager.h"
// Sets default values
ASkill2_Actor::ASkill2_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxColider = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	NiagaraParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE"));
	SetRootComponent(NiagaraParticle);
	BoxColider->SetupAttachment(NiagaraParticle);
	BoxColider->SetCollisionProfileName("PlayerSkill");
	BoxColider->OnComponentHit.AddDynamic(this, &ASkill2_Actor::OnHit_Skil2);
	// 오버랩 인벤트 활성화
	BoxColider->SetGenerateOverlapEvents(true); // 안전하게 켜두기
	BoxColider->OnComponentBeginOverlap.AddDynamic(this, &ASkill2_Actor::OnCapsuleBeginOverlap_Skil2);
	BoxColider->OnComponentEndOverlap.AddDynamic(this, &ASkill2_Actor::OnCapsuleEndOverlap_Skil2);
}

// Called when the game starts or when spawned
void ASkill2_Actor::BeginPlay()
{
	Super::BeginPlay();
	const FCharacterInfo* Infog = GetWorld()->GetGameInstance()->GetSubsystem<UDataManager>()->GetDatainfo_G();
	const FCharacterInfo* Infow = GetWorld()->GetGameInstance()->GetSubsystem<UDataManager>()->GetDatainfo_W();
	switch (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSelectedcharacter())
	{
	case Characters::Warrior:
		AttAckDamage = Infow->Skill2_ATK;
		break;
	case Characters::Guiden:
		AttAckDamage = Infog->Skill2_ATK;
		break;
	}
	
}
void ASkill2_Actor::OnHit_Skil2(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	FString s = OtherActor->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("skil2_hit:%s"), *s);
	UE_LOG(LogMypro, Warning, TEXT("ATTACKDAMAGE:%f"), AttAckDamage);

}


void ASkill2_Actor::OnCapsuleBeginOverlap_Skil2(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	FString s = OtherActor->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("skil2_overlap:%s"), *s);
	UE_LOG(LogMypro, Warning, TEXT("ATTACKDAMAGE:%f"), AttAckDamage);

}

void ASkill2_Actor::OnCapsuleEndOverlap_Skil2(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	FString s = OtherActor->GetActorLabel();
	UE_LOG(LogMypro, Warning, TEXT("skil2_pverlapend:%s"), *s);
	UE_LOG(LogMypro, Warning, TEXT("ATTACKDAMAGE:%f"), AttAckDamage);

}
// Called every frame
void ASkill2_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

