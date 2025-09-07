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
	// ������ �κ�Ʈ Ȱ��ȭ
	BoxColider->SetGenerateOverlapEvents(true); // �����ϰ� �ѵα�
	BoxColider->OnComponentBeginOverlap.AddDynamic(this, &ASkill1_Actor::OnCapsuleBeginOverlap_Skill);
	BoxColider->OnComponentEndOverlap.AddDynamic(this, &ASkill1_Actor::OnCapsuleEndOverlap_Skill);
}

// Called when the game starts or when spawned
void ASkill1_Actor::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().ClearTimer(Time);
	GetWorld()->GetTimerManager().SetTimer(Time, FTimerDelegate::CreateLambda([this]() {
		Destroy();
		}), ActorDestroyTime, false);
}

void ASkill1_Actor::OnHit_Skill(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	FString s = OtherActor->GetName();
	UE_LOG(LogMypro, Warning, TEXT("skill_hit:%s"), *s);


}


void ASkill1_Actor::OnCapsuleBeginOverlap_Skill(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{

	FString s = OtherActor->GetName();
	UE_LOG(LogMypro, Warning, TEXT("skill_overlap:%s"), *s);
	float pe = static_cast<float>(AttackDamage);
	UGameplayStatics::ApplyDamage(OtherActor,pe, GetInstigatorController(), this, UDamageType::StaticClass());
	UNiagaraSystem* Niagara = LoadObject<UNiagaraSystem>(GetWorld(), TEXT("/Script/Niagara.NiagaraSystem'/Game/Pack_Simple_Particle_Burst/01_Niagara_Systems/NS_Simple_Burst_Level_3.NS_Simple_Burst_Level_3'"));

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara, SweepResult.ImpactPoint);
}

void ASkill1_Actor::OnCapsuleEndOverlap_Skill(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	FString s = OtherActor->GetName();
	UE_LOG(LogMypro, Warning, TEXT("skill_pverlapend:%s"), *s);
}

// Called every frame
void ASkill1_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

