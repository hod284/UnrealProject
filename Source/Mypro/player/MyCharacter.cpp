// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraHead = CreateDefaultSubobject<USceneComponent>(TEXT("CameraHead"));
	CameraHead->SetupAttachment(RootComponent);
	SpringArm->SetupAttachment(CameraHead);
	Camera->SetupAttachment(SpringArm);
	GetCapsuleComponent()->SetCollisionProfileName("player");
	SetGenericTeamId(FGenericTeamId(TeamPlayer));
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
	PlaySceneObject = Cast<APlaySceneObject>(GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetPlayerLevelObject());
	LookAt = true;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (BackMoving)
	{
		Time += DeltaTime * 3.f;
		FVector NewLoc = FMath::VInterpTo(GetActorLocation(), NewLocation, DeltaTime*3.f, 5.0f);
		SetActorLocation(NewLoc);
		FVector size = GetActorLocation() - NewLocation;
		UE_LOG(LogMypro, Warning, TEXT("%f"), size.Size());
		// 너무 가까우면 스냅 + 종료 처리(지터 방지)
		if (Time >= 1.5f)
		{
			BackMoving = false;
			CurrentVelocity = FVector::Zero();
			Time = 0.0f;
		}
	}
	if (LookAt)
	{
		float radious = FMath::Cos(FMath::DegreesToRadians(45.0f));
		AActor* CameraTarget = PlaySceneObject->GetMonster(TEXT("Monster_BOSS"));
		// 몬스터월드 로케이션
		FVector TargetLocation = CameraTarget->GetActorLocation();
		// 캐릭터 월드로케이션
		FVector CameraLocation = GetActorLocation();
		float Angle = FVector::DotProduct(GetActorForwardVector(),(CameraLocation - TargetLocation).GetSafeNormal());
		UE_LOG(LogMypro, Warning, TEXT("Angle : %f"), Angle);
		UE_LOG(LogMypro, Warning, TEXT("RADIOUS : %f"), radious);
		if (Angle > 0)
		{
			CameraHead->SetRelativeRotation(FRotator(0, 180, 0));
		}
		else
		{
			CameraHead->SetRelativeRotation(FRotator(0, 0, 0));
		}
		if ( Angle <= radious && Angle < 0)
		{
			FVector To = CameraTarget->GetActorLocation();     // 타깃월드포지션
			FVector From = Camera->GetComponentLocation(); // 카메라 월드 위치
			const FRotator Desired = UKismetMathLibrary::FindLookAtRotation(From, To);
			const FRotator Smoothed = FMath::RInterpTo(Camera->GetComponentRotation(),
				Desired, DeltaTime, 5 /*예:5~12*/);
			Camera->SetWorldRotation(Smoothed);
		}
		else
		{
			Camera->SetRelativeRotation(FRotator(Camera->GetRelativeRotation().Pitch, 0, 0));
		}
	}
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
		EnhancedInputComponent->BindAction(InputManager->MouseMove, ETriggerEvent::Triggered, this, &AMyCharacter::CameraRotation);
		EnhancedInputComponent->BindAction(InputManager->RightCusorDown, ETriggerEvent::Triggered, this, &AMyCharacter::CameraRotation_Allow);
		EnhancedInputComponent->BindAction(InputManager->RightCusorDown, ETriggerEvent::Completed, this, &AMyCharacter::CameraRotation_Cancel);
		EnhancedInputComponent->BindAction(InputManager->RightCusorDown, ETriggerEvent::Canceled, this, &AMyCharacter::CameraRotation_Cancel);
		EnhancedInputComponent->BindAction(InputManager->Move, ETriggerEvent::Completed, this, &AMyCharacter::MoveStop);
		EnhancedInputComponent->BindAction(InputManager->Move, ETriggerEvent::Canceled, this, &AMyCharacter::MoveStop);
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
	if (!BackMoving)
	{
		FVector Diret = Value.Get<FVector>();
		// 캐릭터 무브먼트에게 이동한다고 신호 보내는 함수
		AddMovementInput(GetActorForwardVector(),  Diret.X);
		AddMovementInput(GetActorRightVector(), Diret.Y);
		IsMoving = true;
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
			{
				GetMesh()->SetRelativeRotation(FRotator(0, 0.0f, 0));
			}

			else if (Diret.Y < 0.f)
			{
				GetMesh()->SetRelativeRotation(FRotator(0, -180.0f, 0));
			}
		}
		//현재 속도(velocity) 벡터를 “안전하게” 정규화해서 방향만 뽑은 단위 벡터 구하는 함수
		// GetVelocity().GetSafeNormal()  
		//GetVelocity().GetSafeNormal() 이걸 이용해서 최신상태가 어디로 바로보고 있는지 저장
		CurrentVelocity = GetVelocity().GetSafeNormal();
	}
}
void AMyCharacter::MoveStop(const FInputActionValue& Value)
{
	IsMoving = false;
}
void AMyCharacter::CameraRotation(const FInputActionValue& Value)
{
	FVector Diret = Value.Get<FVector>();
	if (!LookAt)
	{
		float	Pitch = Diret.Y * 90.f * GetWorld()->GetDeltaSeconds();
		float	Yaw = Diret.X * 90.f * GetWorld()->GetDeltaSeconds();
		Camera->AddRelativeRotation(FRotator(Pitch, Yaw, 0));
		FRotator Rot = Camera->GetRelativeRotation();

		if (Rot.Pitch < -70.0)
			Rot.Pitch = -70.0;

		else if (Rot.Pitch > 70.0)
			Rot.Pitch = 70.0;

		if (Rot.Yaw < -90.0)
			Rot.Yaw += 360.0;

		else if (Rot.Yaw > 270.0)
			Rot.Yaw -= 360.0;
		Camera->SetRelativeRotation(Rot);
	}
}
void AMyCharacter::CameraRotation_Allow(const FInputActionValue& Value)
{
	LookAt=false;
}

void AMyCharacter::CameraRotation_Cancel(const FInputActionValue& Value)
{
	LookAt = true;
	Camera->SetRelativeRotation(FRotator(Camera->GetRelativeRotation().Pitch, 0, 0));
}

void AMyCharacter::BackKey(const FInputActionValue& Value)
{
	if (!IsMoving)
	{
		// 단위 백터니까 방향만 가지고 있음 방향백터 x거리
		FVector Backward = CurrentVelocity * -600.0f; // 뒤로 20만큼
		NewLocation = GetActorLocation() + Backward;
		BackMoving = true;
		if (AnimInstance)
			AnimInstance->PlayBack();
	}
}
void AMyCharacter::AttackKey(const FInputActionValue& Value)
{
	if (AnimInstance&&!IsMoving)
		AnimInstance->PlayAttack();
}

void AMyCharacter::Skill1Key(const FInputActionValue& Value)
{
	if (AnimInstance && !IsMoving)
		AnimInstance->PlaySkill(0);
}

void AMyCharacter::Skill2Key(const FInputActionValue& Value)
{
	if (AnimInstance && !IsMoving)
		AnimInstance->PlaySkill(1);
}

void AMyCharacter::Skill3Key(const FInputActionValue& Value)
{
	if (AnimInstance && !IsMoving)
		AnimInstance->PlaySkill(2);
}

void AMyCharacter::Skill4Key(const FInputActionValue& Value)
{
	if (AnimInstance && !IsMoving)
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

