// Fill out your copyright notice in the Description page of Project Settings.

#include "SelectCharacter.h"
#include  "../common/IntroSceneObject.h"
// Sets default values
ASelectCharacter::ASelectCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsulComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	SetRootComponent(CapsulComponent);
	SkeletalMeshComponent->SetupAttachment(CapsulComponent);
	Niagara->SetupAttachment(CapsulComponent);
	CameraComponent->SetupAttachment(SpringArm);
	SpringArm->SetupAttachment(CapsulComponent);
	SkeletalMeshComponent->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> GetParticle(TEXT("/Script/Niagara.NiagaraSystem'/Game/material/magionaprticle.magionaprticle'"));
	Niagara->SetAutoActivate(false);
	if (GetParticle.Succeeded())
	{
		UNiagaraSystem* pa = GetParticle.Object;
		Niagara->SetAsset(pa);
	}
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsulComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CapsulComponent->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
}

// Called when the game starts or when spawned
void ASelectCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASelectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsHover)
	{
		UE_LOG(	LogMypro, Warning, TEXT("HOVER"));
		SkeletalMeshComponent->SetCustomDepthStencilValue(3);
	}
	else
		SkeletalMeshComponent->SetCustomDepthStencilValue(0);
}

void ASelectCharacter::NotifyActorBeginCursorOver()
{
	IsHover = true;
}

void ASelectCharacter::NotifyActorEndCursorOver()
{
	IsHover = false;
}

void ASelectCharacter::NotifyActorOnClicked(FKey ButtonPressed)
{
	CapsulComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AIntroSceneObject* IntroSceneObject = Cast<AIntroSceneObject>(UGameplayStatics::GetActorOfClass(GetWorld(), AIntroSceneObject::StaticClass()));
	if (IntroSceneObject)
	{
		IntroSceneObject->CallthePlayCharacter(GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSelectedcharacter());
	}
}

// Called to bind functionality to input
void ASelectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASelectCharacter::Selected()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->SetViewTargetWithBlend(this,2.0f);
	GetWorldTimerManager().ClearTimer(Timerahbdle);
	GetWorld()->GetTimerManager().SetTimer(Timerahbdle,this,&ASelectCharacter::SelectedAnimation,2.0f, false);
	Niagara->SetVisibility(false);
}

void ASelectCharacter::SelectedAnimation()
{
	SkeletalMeshComponent->PlayAnimation(SelectedAnim, false);
	GetWorldTimerManager().ClearTimer(Timerahbdle);
	GetWorld()->GetTimerManager().SetTimer(Timerahbdle, this, &ASelectCharacter::idleAnimation, SelectedAnim->GetPlayLength()+0.5f, false);
}

void ASelectCharacter::idleAnimation()
{
	SkeletalMeshComponent->PlayAnimation(idle, true);
}

void ASelectCharacter::Inite()
{
	GetWorldTimerManager().ClearTimer(Timerahbdle);
	SkeletalMeshComponent->PlayAnimation(idle, true);
}

void ASelectCharacter::StartGame()
{
	Niagara->SetVisibility(true);
	Niagara->Activate();
}




