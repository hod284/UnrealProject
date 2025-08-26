// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill4_Magition.h"

// Sets default values
ASkill4_Magition::ASkill4_Magition()
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
void ASkill4_Magition::BeginPlay()
{
	Super::BeginPlay();
	
}
void ASkill4_Magition::OnHit_Skil4_Magition(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{


}
void ASkill4_Magition::OnCapsuleBeginOverlap_Skil4_Magition(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{


}
void ASkill4_Magition::OnCapsuleEndOverlap_Skil4_Magition(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{


}
// Called every frame
void ASkill4_Magition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

