// Fill out your copyright notice in the Description page of Project Settings.


#include "Action3_Monster.h"

// Sets default values
AAction3_Monster::AAction3_Monster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxColider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BOX"));
	NiagaraParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE"));
	SetRootComponent(NiagaraParticle);
	BoxColider->SetupAttachment(NiagaraParticle);
	BoxColider->SetCollisionProfileName("Monsterskill");
	BoxColider->OnComponentHit.AddDynamic(this, &AAction3_Monster::OnHit_Action3_M);
	// 오버랩 인벤트 활성화
	BoxColider->SetGenerateOverlapEvents(true); // 안전하게 켜두기
	BoxColider->OnComponentBeginOverlap.AddDynamic(this, &AAction3_Monster::OnCapsuleBeginOverlap_Action3_M);
	BoxColider->OnComponentEndOverlap.AddDynamic(this, &AAction3_Monster::OnCapsuleEndOverlap_Action3_M);
}

// Called when the game starts or when spawned
void AAction3_Monster::BeginPlay()
{
	Super::BeginPlay();
	FHitResult result;
	ECollisionChannel Ch = ECollisionChannel::ECC_GameTraceChannel1;
	FVector Start = GetActorLocation();
	FVector End = Start + GetActorUpVector() * 3000.f;
	bool bHit = GetWorld()->LineTraceSingleByChannel(result, Start, End, Ch);
	DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Red : FColor::Green, false, 0.3f, 0, 1.f);
	if (bHit)
	{
		FVector f = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
		FVector e = FVector(result.ImpactPoint.X, result.ImpactPoint.Y, 0);

		UE_LOG(LogMypro, Warning, TEXT("beamlength:%s"), *result.GetActor()->GetActorLabel());

		NiagaraParticle->SetVariableFloat(TEXT("BeamLength"), result.Distance);
		BoxColider->SetCapsuleHalfHeight(result.Distance);
		BoxColider->SetRelativeLocation(FVector( 0, 0, result.Distance));
	}
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

