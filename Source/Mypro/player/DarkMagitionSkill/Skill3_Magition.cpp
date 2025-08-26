// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill3_Magition.h"

// Sets default values
ASkill3_Magition::ASkill3_Magition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxColider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BOX"));
	NiagaraParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE"));
	SetRootComponent(NiagaraParticle);
	BoxColider->SetupAttachment(NiagaraParticle);
	BoxColider->SetCollisionProfileName("PlayerSkill");
}

// Called when the game starts or when spawned
void ASkill3_Magition::BeginPlay()
{
	Super::BeginPlay();
	
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


}
void ASkill3_Magition::OnCapsuleBeginOverlap_Skil3_Magition(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{


}
void ASkill3_Magition::OnCapsuleEndOverlap_Skil3_Magition(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{


}
