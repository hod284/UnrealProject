// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalClass.h"
#include "../player/MyCharacter.h"
// Sets default values
APortalClass::APortalClass()
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
	Sphere->OnComponentHit.AddDynamic(this, &APortalClass::OnHit);
	// ������ �κ�Ʈ Ȱ��ȭ
	Sphere->SetGenerateOverlapEvents(true); // �����ϰ� �ѵα�
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &APortalClass::OnCapsuleBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &APortalClass::OnCapsuleEndOverlap);
}

// Called when the game starts or when spawned
void APortalClass::BeginPlay()
{
	Super::BeginPlay();
}

void APortalClass::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	AMyCharacter* ch = Cast<AMyCharacter>(OtherActor);
	if (ch)
	{
		if (ch->GetCanPortal())
		{
			APlayerController* PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
			AMyPlayerState* PS = Cast<AMyPlayerState>(PC->PlayerState);
			if (IsValid(PS))
				PS->Inventoryco->ItemMinus.Broadcast("Portal");
			UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Virtual_Studio_Kit/Maps/TrackerlessStudio"));
		}
	}
}
void APortalClass::OnCapsuleBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{


}
void APortalClass::OnCapsuleEndOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{


}

// Called every frame
void APortalClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortalClass::SetNoColision()
{
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
void APortalClass::SetColision()
{
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}