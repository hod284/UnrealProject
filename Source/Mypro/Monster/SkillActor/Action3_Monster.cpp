// Fill out your copyright notice in the Description page of Project Settings.


#include "Action3_Monster.h"

// Sets default values
AAction3_Monster::AAction3_Monster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Transform = CreateDefaultSubobject<USceneComponent>(TEXT("tr"));
	BoxColider = CreateDefaultSubobject<USphereComponent>(TEXT("BOX"));
	NiagaraParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE"));
	SetRootComponent(Transform);
	NiagaraParticle->SetupAttachment(Transform);
	BoxColider->SetupAttachment(Transform);
	BoxColider->SetCollisionProfileName("Monsterskill");
}

// Called when the game starts or when spawned
void AAction3_Monster::BeginPlay()
{
	Super::BeginPlay();
	
}


void AAction3_Monster::OnHit_Action3_M(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{


}
void AAction3_Monster::OnCapsuleBeginOverlap_Action3_M(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	

}
void AAction3_Monster::OnCapsuleEndOverlap_Action3_M(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	

}

// Called every frame
void AAction3_Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

