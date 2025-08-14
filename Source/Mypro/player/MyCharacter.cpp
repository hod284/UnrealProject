// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance = Cast<UMyPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	AMainPlayerController* PlayerController = Cast<AMainPlayerController>(GetController());
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		Subsystem->AddMappingContext(GetWorld()->GetGameInstance()->GetSubsystem<UInputManager>()->Context, 0);
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		const UInputManager* InputManager = GetWorld()->GetGameInstance()->GetSubsystem<UInputManager>();
		EnhancedInputComponent->BindAction(InputManager->Move, ETriggerEvent::Triggered, this, &AMyCharacter::MoveKey);
		EnhancedInputComponent->BindAction(InputManager->Back, ETriggerEvent::Started, this, &AMyCharacter::BackKey);
		EnhancedInputComponent->BindAction(InputManager->Attack, ETriggerEvent::Started, this, &AMyCharacter::AttackKey);
		EnhancedInputComponent->BindAction(InputManager->Skill1, ETriggerEvent::Started, this, &AMyCharacter::Skill1Key);
		EnhancedInputComponent->BindAction(InputManager->Skill2, ETriggerEvent::Started, this, &AMyCharacter::Skill2Key);
		EnhancedInputComponent->BindAction(InputManager->Skill3, ETriggerEvent::Started, this, &AMyCharacter::Skill3Key);
		EnhancedInputComponent->BindAction(InputManager->Skill4, ETriggerEvent::Started, this, &AMyCharacter::Skill4Key);
	}
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void AMyCharacter::MoveKey(const FInputActionValue& Value)
{
	FVector Diret = Value.Get<FVector>();
	// 캐릭터 무브먼트에게 이동한다고 신호 보내는 함수
	AddMovementInput(GetActorForwardVector(), Diret.X);
	AddMovementInput(GetActorRightVector(), Diret.Y);
	// 앞, 뒤 둘중 한 방향으로 움직이도록 키를 눌렀을 경우
	if (Diret.X > 0.f)
	{
		AnimInstance->SetDir(0.f);
		GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));
		SetActorRotation(FRotator(0, 0.0f, 0));
		if (Diret.Y > 0.f)
		{
			GetMesh()->SetRelativeRotation(FRotator(0, -45.0f, 0));
			SetActorRotation(FRotator(0, 45.0f, 0));
			AnimInstance->SetDir(45.f);
		}

		else if (Diret.Y < 0.f)
		{
			GetMesh()->SetRelativeRotation(FRotator(0, -135.0f, 0));
			SetActorRotation(FRotator(0, -45.0f, 0));
			AnimInstance->SetDir(-45.f);
		}
	}

	else if (Diret.X < 0.f)
	{
		AnimInstance->SetDir(180.f);
		GetMesh()->SetRelativeRotation(FRotator(0, -270.0f, 0));
		SetActorRotation(FRotator(0, 180.0f, 0));
		if (Diret.Y > 0.f)
		{
			GetMesh()->SetRelativeRotation(FRotator(0, -315.0f, 0));
			SetActorRotation(FRotator(0, 135.0f, 0));
			AnimInstance->SetDir(135.f);
		}

		else if (Diret.Y < 0.f)
		{
			GetMesh()->SetRelativeRotation(FRotator(0, -225.0f, 0));
			SetActorRotation(FRotator(0, -135.0f, 0));
			AnimInstance->SetDir(-135.f);
		}
	}

	else
	{
		if (Diret.Y > 0.f)
		{
			SetActorRotation(FRotator(0, 90.0f, 0));
			GetMesh()->SetRelativeRotation(FRotator(0 ,0.0f,0));
		}

		else if (Diret.Y < 0.f)
		{
			SetActorRotation(FRotator(0, -90.0f, 0));
			GetMesh()->SetRelativeRotation(FRotator(0, -180.0f, 0));
		}
	}
	//현재 속도(velocity) 벡터를 “안전하게” 정규화해서 방향만 뽑은 단위 벡터 구하는 함수
	// GetVelocity().GetSafeNormal()  
	//GetVelocity().GetSafeNormal() 이걸 이용해서 최신상태가 어디로 바로보고 있는지 저장
	CurrentVelocity = GetVelocity().GetSafeNormal();
}
void AMyCharacter::BackKey(const FInputActionValue& Value)
{
	// 단위 백터니까 방향만 가지고 있음 방향백터 x거리
	FVector Backward = CurrentVelocity * -200.0f; // 뒤로 20만큼
	FVector NewLocation = GetActorLocation() + Backward;
	SetActorLocation(NewLocation);
	CurrentVelocity = FVector::Zero();
	if (AnimInstance)
		AnimInstance->PlayBack();
}
void AMyCharacter::AttackKey(const FInputActionValue& Value)
{
	if (AnimInstance)
		AnimInstance->PlayAttack();
}

void AMyCharacter::Skill1Key(const FInputActionValue& Value)
{
	if (AnimInstance)
		AnimInstance->PlaySkill(0);
}

void AMyCharacter::Skill2Key(const FInputActionValue& Value)
{
	if (AnimInstance)
		AnimInstance->PlaySkill(1);
}

void AMyCharacter::Skill3Key(const FInputActionValue& Value)
{
	if (AnimInstance)
		AnimInstance->PlaySkill(2);
}

void AMyCharacter::Skill4Key(const FInputActionValue& Value)
{
	if (AnimInstance)
		AnimInstance->PlaySkill(3);
}

void AMyCharacter::NAttack()
{
}

void AMyCharacter::Skill1()
{
}

void AMyCharacter::Skill2()
{
}

void AMyCharacter::Skill3()
{
}

void AMyCharacter::Skill4()
{
}

