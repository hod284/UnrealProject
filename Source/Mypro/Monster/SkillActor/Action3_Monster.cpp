// Fill out your copyright notice in the Description page of Project Settings.


#include "Action3_Monster.h"
// Sets default values
AAction3_Monster::AAction3_Monster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("se"));
	BoxColider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BOX"));
	NiagaraParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE"));
	SetRootComponent(Scene);
	NiagaraParticle ->SetupAttachment(Scene);
	BoxColider->SetupAttachment(Scene);
	BoxColider->SetCollisionProfileName("Monsterskill");
	BoxColider->OnComponentHit.AddDynamic(this, &AAction3_Monster::OnHit_Action3_M);
	// ������ �κ�Ʈ Ȱ��ȭ
	BoxColider->SetGenerateOverlapEvents(true); // �����ϰ� �ѵα�
	BoxColider->OnComponentBeginOverlap.AddDynamic(this, &AAction3_Monster::OnCapsuleBeginOverlap_Action3_M);
	BoxColider->OnComponentEndOverlap.AddDynamic(this, &AAction3_Monster::OnCapsuleEndOverlap_Action3_M);
}

// Called when the game starts or when spawned
void AAction3_Monster::BeginPlay()
{
	Super::BeginPlay();
	NiagaraParticle->SetActive(false);
	BoxColider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
	FString s = OtherActor->GetName();
	UE_LOG(LogMypro, Warning, TEXT("AC3_overlap:%s"), *s);
	float pe = static_cast<float>(AttackDamage);
	UGameplayStatics::ApplyDamage(OtherActor, pe, GetInstigatorController(), this, UDamageType::StaticClass());
	BoxColider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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

void AAction3_Monster::Init()
{
	FHitResult result;
	ECollisionChannel Ch = ECollisionChannel::ECC_GameTraceChannel1;
	FVector Start = GetActorLocation();
	FVector End = Start + GetActorForwardVector() * 3000.f;
	bool bHit = GetWorld()->LineTraceSingleByChannel(result, Start, End, Ch);
	DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Red : FColor::Green, false, 0.3f, 0, 1.f);
	if (bHit)
	{
		FVector f = FVector(GetActorLocation().X, GetActorLocation().Y, 0);
		FVector e = FVector(result.ImpactPoint.X, result.ImpactPoint.Y, 0);
		float dis = FVector::Dist(result.ImpactPoint, GetActorLocation());
		UE_LOG(LogMypro, Warning, TEXT("beamlength:%s"), *result.GetActor()->GetName());
		UE_LOG(LogMypro, Warning, TEXT("result.impactp[oint:%s"), *result.ImpactPoint.ToString());
		UE_LOG(LogMypro, Warning, TEXT("startlocation:%s"), *GetActorLocation().ToString());
		NiagaraParticle->SetVariableFloat(TEXT("BeamLength"),dis);
		BoxColider->SetCapsuleHalfHeight(dis/2.0f);
		BoxColider->SetRelativeLocation(FVector(0, 0, dis/2.0f));
	}
	NiagaraParticle->SetActive(true);
	BoxColider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AAction3_Monster::Reset()
{
	BoxColider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	NiagaraParticle->SetActive(false);
}

