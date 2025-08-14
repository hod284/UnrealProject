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
	CapsulComponent->bVisualizeComponent = true;
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
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SkeletalMeshComponent->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
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
		/*
		SetCustomDepthStencilValue(스텐실 = 번호표(마스크)
		숫자에 따라 바꿀 수 있는 것들(예시)
적용 여부: CustomStencil == 5인 픽셀만 효과 O

색상: 1=빨강, 2=파랑, 3=금색 …

외곽선 두께/밝기: 1=얇게, 2=두껍게

글로우 강도/블룸/채도 등 모든 PP 파라미터
		*/
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
	SkeletalMeshComponent->SetCustomDepthStencilValue(0);
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
	// 로컬 플레이어 컨트롤러를 가져온다.
	// 0을 넣는 부분에는 멀티일경우숫자에 따라 다른 클라이언트 플레이어 컨트롤러를 가져올 수 있다.
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	
		PlayerController->SetViewTargetWithBlend(this,2.0f);
		//유니티 코루틴처럼 일정시간후 실행되도록 만드는 언리얼에 들어가있는  타이머를 사용
	//clear 타이머를 사용하여 이전에 설정된 타이머를 제거하고 새로 설정한다.
	GetWorldTimerManager().ClearTimer(Timerahbdle);
	//타이머를 설정한다 
	/*
	GetWorld()->GetTimerManager().SetTimer(
		AnimationTriggerTimer, // 타이머 핸들 변수 이름
		this, // this는 현재 클래스의 인스턴스를 가리킴
		&AMyActor::PlayMyAnimation,// 2초 후 실행할 함수
        2.0f, // 2초 후 실행
		false // false는 타이머가 한 번만 실행되도록 설정 (true로 설정하면 반복 실행됨)
	*/
	GetWorld()->GetTimerManager().SetTimer(Timerahbdle,this,&ASelectCharacter::SelectedAnimation,2.0f, false);
	//
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




