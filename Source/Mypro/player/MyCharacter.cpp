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
		EnhancedInputComponent->BindAction(InputManager->Back, ETriggerEvent::Triggered, this, &AMyCharacter::BackKey);
		EnhancedInputComponent->BindAction(InputManager->Attack, ETriggerEvent::Triggered, this, &AMyCharacter::AttackKey);
		EnhancedInputComponent->BindAction(InputManager->Skill1, ETriggerEvent::Triggered, this, &AMyCharacter::Skill1Key);
		EnhancedInputComponent->BindAction(InputManager->Skill2, ETriggerEvent::Triggered, this, &AMyCharacter::Skill2Key);
		EnhancedInputComponent->BindAction(InputManager->Skill3, ETriggerEvent::Triggered, this, &AMyCharacter::Skill3Key);
		EnhancedInputComponent->BindAction(InputManager->Skill3, ETriggerEvent::Triggered, this, &AMyCharacter::Skill4Key);
	}
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void AMyCharacter::MoveKey(const FInputActionValue& Value)
{
	FVector Diret = Value.Get<FVector>();
	AddMovementInput(GetActorForwardVector(), Diret.X);
	AddMovementInput(GetActorRightVector(), Diret.Y);
	// 앞, 뒤 둘중 한 방향으로 움직이도록 키를 눌렀을 경우
	if (Diret.X > 0.f)
	{
		AnimInstance->SetDir(0.f);
		GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));
		if (Diret.Y > 0.f)
		{
			GetMesh()->SetRelativeRotation(FRotator(0, -45.0f, 0));
			AnimInstance->SetDir(45.f);
		}

		else if (Diret.Y < 0.f)
		{
			GetMesh()->SetRelativeRotation(FRotator(0, -135.0f, 0));
			AnimInstance->SetDir(-45.f);
		}
	}

	else if (Diret.X < 0.f)
	{
		AnimInstance->SetDir(180.f);
		GetMesh()->SetRelativeRotation(FRotator(0, -270.0f, 0));
		if (Diret.Y > 0.f)
		{
			GetMesh()->SetRelativeRotation(FRotator(0, -315.0f, 0));
			AnimInstance->SetDir(135.f);
		}

		else if (Diret.Y < 0.f)
		{
			GetMesh()->SetRelativeRotation(FRotator(0, -225.0f, 0));
			AnimInstance->SetDir(-135.f);
		}
	}

	else
	{
		if (Diret.Y > 0.f)
			GetMesh()->SetRelativeRotation(FRotator(0 ,0.0f,0));

		else if (Diret.Y < 0.f)
			GetMesh()->SetRelativeRotation(FRotator(0, -180.0f, 0));
	}
}
void AMyCharacter::BackKey(const FInputActionValue& Value)
{
	
	AddMovementInput(GetActorForwardVector(), -2.0f);
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

