// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPortalClass.h"

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
}

// Called when the game starts or when spawned
void ASpawnPortalClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnPortalClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

