// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPortalClass.h"
#include "../player/MyCharacter.h"
// Sets default values
ASpawnPortalClass::ASpawnPortalClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	Niagara1 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("n1"));
	Niagara2 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("n2"));
	Niagara3 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("n3"));
	Niagara4 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("n4"));
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("box"));
	SetRootComponent(Sphere);
	Niagara1->SetupAttachment(Sphere);
	Niagara2->SetupAttachment(Niagara1);
	Niagara3->SetupAttachment(Niagara1);
	Niagara4->SetupAttachment(Niagara1);
	StaticMesh->SetupAttachment(Sphere);
	static ConstructorHelpers::FClassFinder<UMonsterHPBar>Minion_s(TEXT("/Script/Engine.Blueprint'/Game/bluePrint/MinionSupor.MinionSupor_C'"));
	if (Minion_s.Succeeded())
	Minion = Minion_s.Class;
	static ConstructorHelpers::FClassFinder<UMonsterHPBar>Minion_sH(TEXT("/Script/Engine.Blueprint'/Game/bluePrint/MinionShooting.MinionShooting_C'"));
	if (Minion_sH.Succeeded())
		Minion_gun = Minion_sH.Class;
	Sphere->OnComponentHit.AddDynamic(this, &ASpawnPortalClass::OnHit);
	Sphere->SetGenerateOverlapEvents(true); // ??????? ??ес?
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASpawnPortalClass::OnCapsuleBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ASpawnPortalClass::OnCapsuleEndOverlap);
}

// Called when the game starts or when spawned
void ASpawnPortalClass::BeginPlay()
{
	Super::BeginPlay();
	GottotheMain = false;
}

// Called every frame
void ASpawnPortalClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void  ASpawnPortalClass::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	AMyCharacter* ch = Cast<AMyCharacter>(OtherActor);
	if (ch)
	{
		GottotheMain = true;
	}
}
void  ASpawnPortalClass::OnCapsuleBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{


}
void  ASpawnPortalClass::OnCapsuleEndOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{


}

void ASpawnPortalClass::Spawn()
{
	FActorSpawnParameters parametor;
	parametor.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	parametor.Owner = this;
	APawn* spawn1 = GetWorld()->SpawnActor<APawn>(Minion, FVector(140, -550, 90), FRotator(0, 90, 0), parametor);
	APawn* spawn2 = GetWorld()->SpawnActor<APawn>(Minion_gun, FVector(-90, -550, 90), FRotator(0, 90, 0), parametor);
}

