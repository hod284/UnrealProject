// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill1_Magition.h"

// Sets default values
ASkill1_Magition::ASkill1_Magition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxColider = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	NiagaraParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE"));
	SetRootComponent(NiagaraParticle);
	BoxColider->SetupAttachment(NiagaraParticle);
	BoxColider->SetCollisionProfileName("PlayerSkill");
}

// Called when the game starts or when spawned
void ASkill1_Magition::BeginPlay()
{
	Super::BeginPlay();
	
}
void ASkill1_Magition::OnHit_Skil1_Magition(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{


}
void ASkill1_Magition::OnCapsuleBeginOverlap_Skil1_Magition(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{


}
void ASkill1_Magition::OnCapsuleEndOverlap_Skil1_Magition(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{


}
// Called every frame
void ASkill1_Magition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

