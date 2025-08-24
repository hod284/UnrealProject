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
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->OnComponentHit.AddDynamic(this, &AMyCharacter::OnHit);
	Capsule->SetGenerateOverlapEvents(true); // �����ϰ� �ѵα�
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnCapsuleBeginOverlap);
	Capsule->OnComponentEndOverlap.AddDynamic(this, &AMyCharacter::OnCapsuleEndOverlap);
	UCharacterMovementComponent* Move = GetCharacterMovement();
	SavedGroundFriction = Move->GroundFriction;
	SavedBrakingFriction = Move->BrakingFriction;
	SavedBrakingDecel = Move->BrakingDecelerationWalking;
}
void AMyCharacter::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{

}

void AMyCharacter::OnCapsuleBeginOverlap(UPrimitiveComponent* Comp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32, bool bFromSweep,
	const FHitResult& Sweep)
{

	// TODO: ���ϴ� ó��
}
void AMyCharacter::OnCapsuleEndOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	// TODO: ���ϴ� ó��
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (LookAt)
	{
		float radious = FMath::Cos(FMath::DegreesToRadians(45.0f));
		AActor* CameraTarget = PlaySceneObject->GetMonster(TEXT("Monster_BOSS"));
		// ���Ϳ��� �����̼�
		FVector TargetLocation = CameraTarget->GetActorLocation();
		// ĳ���� ��������̼�
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
			FVector To = CameraTarget->GetActorLocation();     // Ÿ�����������
			FVector From = Camera->GetComponentLocation(); // ī�޶� ���� ��ġ
			const FRotator Desired = UKismetMathLibrary::FindLookAtRotation(From, To);
			const FRotator Smoothed = FMath::RInterpTo(Camera->GetComponentRotation(),
				Desired, DeltaTime, 5 /*��:5~12*/);
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
void AMyCharacter::EndDash()
{
	UCharacterMovementComponent* Move = GetCharacterMovement();
	// ��� �̲�������: ����/������ ����
	Move->bUseSeparateBrakingFriction = false;
	Move->GroundFriction = SavedGroundFriction;
	Move->BrakingFriction = SavedBrakingFriction;
	Move->BrakingDecelerationWalking = SavedBrakingDecel;
	BackMoving = false;
	CurrentVelocity = FVector::ZeroVector;
}
void AMyCharacter::MoveKey(const FInputActionValue& Value)
{
	if (!BackMoving)
	{
		FVector Diret = Value.Get<FVector>();
		// ĳ���� �����Ʈ���� �̵��Ѵٰ� ��ȣ ������ �Լ�
		AddMovementInput(GetActorForwardVector(),  Diret.X);
		AddMovementInput(GetActorRightVector(), Diret.Y);
		IsMoving = true;
		// ��, �� ���� �� �������� �����̵��� Ű�� ������ ���
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
		//���� �ӵ�(velocity) ���͸� �������ϰԡ� ����ȭ�ؼ� ���⸸ ���� ���� ���� ���ϴ� �Լ�
		// GetVelocity().GetSafeNormal()  
		//GetVelocity().GetSafeNormal() �̰� �̿��ؼ� �ֽŻ��°� ���� �ٷκ��� �ִ��� ����
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
		UCharacterMovementComponent* Move = GetCharacterMovement();
		// ��� �̲�������: ����/������ ����
		Move->bUseSeparateBrakingFriction = true;
		Move->GroundFriction = 0.5f;
		Move->BrakingFriction = 0.5f;
		Move->BrakingDecelerationWalking = 250.f;
		// ���� ���ʹϱ� ���⸸ ������ ���� ������� x�Ÿ�
	    FVector	NewLocation = -CurrentVelocity * 1200.0f; // �ڷ� 20��ŭ
		LaunchCharacter(NewLocation, true, false);
		BackMoving = true;
		GetWorldTimerManager().ClearTimer(DashTimer);
		GetWorld()->GetTimerManager().SetTimer(DashTimer, this, &AMyCharacter::EndDash, 0.5, false);
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

