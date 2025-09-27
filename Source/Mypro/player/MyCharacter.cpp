// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include"MyPlayerState.h"
// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraHead = CreateDefaultSubobject<USceneComponent>(TEXT("CameraHead"));
	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle"));
	Damagesh = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageWidget"));
	StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSource"));
	static ConstructorHelpers::FClassFinder<UDamageShowing>UI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/widget/DamageWidget.DamageWidget_C'"));
	if(UI.Succeeded())
	Damagesh->SetWidgetClass(UI.Class);
	Damagesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Damagesh->SetWidgetSpace(EWidgetSpace::Screen);
	Damagesh->SetDrawSize(FVector2D(200, 80));
	Damagesh->SetAbsolute(false, false, false);
	CameraHead->SetupAttachment(RootComponent);
	SpringArm->SetupAttachment(CameraHead);
	Camera->SetupAttachment(SpringArm);
	Damagesh->SetupAttachment(CameraHead);
	Niagara->SetupAttachment(GetMesh());
	GetCapsuleComponent()->SetCollisionProfileName("player");
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetGenericTeamId(FGenericTeamId(TeamPlayer));
    SetReplicates(true);
    SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance = Cast<UMyPlayerAnimInstance>(GetMesh()->GetAnimInstance());
    PlayerController = Cast<AMainPlayerController>(GetController());
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		Subsystem->AddMappingContext(GetWorld()->GetGameInstance()->GetSubsystem<UInputManager>()->Context, 0);
	}
	UDamageShowing* da = Cast<UDamageShowing>(Damagesh->GetWidget());
	da->SetVisibility(ESlateVisibility::Collapsed);
	PlaySceneObject = Cast<APlaySceneObject>(UGameplayStatics::GetActorOfClass(GetWorld(), APlaySceneObject::StaticClass()));
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->OnComponentHit.AddDynamic(this, &AMyCharacter::OnHit);
	Capsule->SetGenerateOverlapEvents(true); 
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnCapsuleBeginOverlap);
	Capsule->OnComponentEndOverlap.AddDynamic(this, &AMyCharacter::OnCapsuleEndOverlap);
	UCharacterMovementComponent* Move = GetCharacterMovement();
	SavedGroundFriction = Move->GroundFriction;
	SavedBrakingFriction = Move->BrakingFriction;
	SavedBrakingDecel = Move->BrakingDecelerationWalking;
	ui = Cast<UPlayMainUI>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetPlayMainUI_widget());
	uipvp = Cast<UPvPUIClass>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetPvP_widget());
	uiParty = Cast<UPartyRoomWidgetClass>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetPartyRoom_widget());
	Niagara->SetVisibility(false);
	if (AMyPlayerState* PS = GetPlayerState<AMyPlayerState>())
	{
		PS->Inventoryco->Itemadd.AddUObject(this, &AMyCharacter::SetAddCanPortal);
		PS->Inventoryco->ItemMinus.AddUObject(this,& AMyCharacter::SetMinusCanPortal);
	}
	GetCharacterMovement()->NetworkSmoothingMode = ENetworkSmoothingMode::Linear;
	if (StimuliSource)
	{
		StimuliSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimuliSource->RegisterForSense(TSubclassOf<UAISense_Hearing>());
		StimuliSource->RegisterWithPerceptionSystem();
		StimuliSource->SetAutoActivate(true);
	}
}
void AMyCharacter::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	FString s = OtherActor->GetName();
	UE_LOG(LogMypro, Warning, TEXT("hit:%s"), *s);
	UMySingleton* GI = Cast<UMySingleton>(UGameplayStatics::GetGameInstance(GetWorld()));
	const FItemtableInfo* itemlist = GI->GetItemInfo();
	if (s.Contains(GI->GetItemInfo()->Name))
	{
		if (AMyPlayerState* PS = GetPlayerState<AMyPlayerState>())
		{
			PS->Inventoryco->Itemadd.Broadcast("Portal");
		}
		OtherActor->Destroy();
	}
}

void AMyCharacter::OnCapsuleBeginOverlap(UPrimitiveComponent* Comp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32, bool bFromSweep,
	const FHitResult& Sweep)
{


}
void AMyCharacter::OnCapsuleEndOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlayerController = Cast<AMainPlayerController>(GetController());
	if (!Canskill1)
	{
		if (ui && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
		{
			Skill1cool -= DeltaTime * Skill1Speed;
			ui->SetPercent1(Skill1cool);
		}
		else if (uipvp && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
		{
			if (PlayerController && PlayerController->IsLocalController()&&HasAuthority())
			{
				Skill1cool -= DeltaTime * Skill1Speed;
				uipvp->SetPercent1(Skill1cool);
			}
			else if(PlayerController&&PlayerController->IsLocalController()&&!HasAuthority())
			{
				Skill1cool -= DeltaTime * Skill1Speed;
				uipvp->SetPercent1_c(Skill1cool);
			}
		}
		else if (uipvp && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
		{
			if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
			{
				Skill1cool -= DeltaTime * Skill1Speed;
				uiParty->SetPercent1(Skill1cool);
			}
			else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
			{
				Skill1cool -= DeltaTime * Skill1Speed;
				uiParty->SetPercent1_c(Skill1cool);
			}
		}
	}
	if (!Canskill2)
	{
		if (ui && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
		{
			Skill2cool -= DeltaTime * Skill2Speed;
			ui->SetPercent2(Skill2cool);
		}
		else if (uipvp && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
		{
			if (PlayerController && PlayerController->IsLocalController()&&HasAuthority())
			{
				Skill2cool -= DeltaTime * Skill2Speed;
				uipvp->SetPercent2(Skill2cool);
			}
			else if (PlayerController && PlayerController->IsLocalController()&&!HasAuthority())
			{
				Skill2cool -= DeltaTime * Skill2Speed;
				uipvp->SetPercent2_c(Skill2cool);
			}
		}
		else if (uipvp && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
		{
			if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
			{
				Skill2cool -= DeltaTime * Skill2Speed;
				uiParty->SetPercent2(Skill2cool);
			}
			else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
			{
				Skill2cool -= DeltaTime * Skill2Speed;
				uiParty->SetPercent2_c(Skill2cool);
			}
		}
	}
	if (!Canskill3)
	{
		if (ui && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
		{
			Skill3cool -= DeltaTime * Skill3Speed;
			ui->SetPercent3(Skill3cool);
		}
		else if (uipvp && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
		{
			if (PlayerController && PlayerController->IsLocalController()&&HasAuthority())
			{
				Skill3cool -= DeltaTime * Skill3Speed;
				uipvp->SetPercent3(Skill3cool);
			}
			else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
			{
				Skill3cool -= DeltaTime * Skill3Speed;
				uipvp->SetPercent3_c(Skill3cool);
			}
		}
		else if (uipvp && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
		{
			if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
			{
				Skill3cool -= DeltaTime * Skill3Speed;
				uiParty->SetPercent3(Skill3cool);
			}
			else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
			{
				Skill3cool -= DeltaTime * Skill3Speed;
				uiParty->SetPercent3_c(Skill3cool);
			}
		}
	}
	if (!Canskill4)
	{
		if (ui && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
		{
			Skill4cool -= DeltaTime * Skill4Speed;
			ui->SetPercent4(Skill4cool);
		}
		else if (uipvp && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
		{
			if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
			{
				Skill4cool -= DeltaTime * Skill4Speed;
				uipvp->SetPercent4(Skill4cool);
			}
			else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
			{
				Skill4cool -= DeltaTime * Skill4Speed;
				uipvp->SetPercent4_c(Skill4cool);
			}
		}
		else if (uipvp && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
		{
			if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
			{
				Skill4cool -= DeltaTime * Skill4Speed;
				uiParty->SetPercent4(Skill4cool);
			}
			else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
			{
				Skill4cool -= DeltaTime * Skill4Speed;
				uiParty->SetPercent4_c(Skill4cool);
			}
		}
	}
	if (Skill1cool < 0.0f)
	{
		Skill1cool = 1.0f;
		Canskill1 = true;
		if (ui && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
		ui->SetPercent1(1.0f);
		else if (uipvp && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
		{
			if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
			uipvp->SetPercent1(1.0f);
			else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
				uipvp->SetPercent1_c(Skill1cool);
		}
		else if (uipvp && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
		{
			if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
				uiParty->SetPercent1(1.0f);
			else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
				uiParty->SetPercent1_c(Skill1cool);
		}
	}
	if (Skill2cool < 0.0f)
	{
		Skill2cool = 1.0f;
		Canskill2 = true;
		if (ui && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
		ui->SetPercent2(1.0f);
		else if (uipvp && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
		{
			if(PlayerController && PlayerController->IsLocalController() && HasAuthority())
			uipvp->SetPercent2(1.0f);
			else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
			uipvp->SetPercent2_c(1.0f);
		}
		else if (uipvp && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
		{
			if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
				uiParty->SetPercent2(1.0f);
			else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
				uiParty->SetPercent2_c(1.0f);
		}
	}
	if (Skill3cool < 0.0f)
	{
		Skill3cool = 1.0f;
		Canskill3 = true;
		if (ui && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
		{
			GetMesh()->SetOverlayMaterial(nullptr);
			Niagara->SetVisibility(false);
			ui->SetPercent3(1.0f);
		}
		else if (uipvp && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
		{
			if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
			uipvp->SetPercent3(1.0f);
			else if(PlayerController && PlayerController->IsLocalController() && !HasAuthority())
				uipvp->SetPercent3_c(1.0f);
		}
		else if (uipvp && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
		{
			if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
				uiParty->SetPercent3(1.0f);
			else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
				uiParty->SetPercent3_c(1.0f);
		}
		if (uipvp && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp ||
			uipvp && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
		{
			if (HasAuthority())
				Multicast_NullOverlap();
			else
				Server_NullOverlap();
		}
		AttackDamage -= AttackDamageUp;
	}
	if (Skill4cool < 0.0f)
	{
		Skill4cool = 1.0f;
		Canskill4 = true;
		if (ui && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
		ui->SetPercent4(1.0f);
		else if (uipvp && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
		{
			if(PlayerController && PlayerController->IsLocalController() && HasAuthority())
			uipvp->SetPercent4(1.0f);
			else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
				uipvp->SetPercent4_c(1.0f);
		}
		else if (uipvp && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
		{
			if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
				uiParty->SetPercent4(1.0f);
			else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
				uiParty->SetPercent4_c(1.0f);
		}
	}
	if (LookAt)
	{
		float radious = FMath::Cos(FMath::DegreesToRadians(45.0f));
		if (PlaySceneObject)
		{
			CameraTarget = PlaySceneObject->GetMonster(TEXT("Monster_C_1"));
		}
		if (CameraTarget != NULL)
		{
		    TargetTransform = CameraTarget->GetRootComponent();
		
			TargetLocation = CameraTarget->GetActorLocation();
			
			AMonster* m = Cast<AMonster>(CameraTarget);
			if (m&&m->GetDeath())
			{
				LookAt = false;
				CameraHead->SetRelativeRotation(FRotator(0, 180, 0));
			}

			FVector CameraLocation = GetActorLocation();
			float Angle = FVector::DotProduct(GetActorForwardVector(), (CameraLocation - TargetLocation).GetSafeNormal());
			if (Angle > 0)
			{
				CameraHead->SetRelativeRotation(FRotator(0, 180, 0));
			}
			else
			{
				CameraHead->SetRelativeRotation(FRotator(0, 0, 0));
			}
			if (Angle <= radious || Angle >= -radious)
			{
				FVector To = CameraTarget->GetActorLocation();     
				FVector From = Camera->GetComponentLocation(); 
				const FRotator Desired = UKismetMathLibrary::FindLookAtRotation(From, To);
				const FRotator Smoothed = FMath::RInterpTo(Camera->GetComponentRotation(),
					Desired, DeltaTime, 5 );
				Camera->SetWorldRotation(Smoothed);
			}
			else
			{
				Camera->SetRelativeRotation(FRotator(Camera->GetRelativeRotation().Pitch, 0, 0));
			}
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
		EnhancedInputComponent->BindAction(InputManager->Dash, ETriggerEvent::Started, this, &AMyCharacter::DashKey);
		EnhancedInputComponent->BindAction(InputManager->Inventory, ETriggerEvent::Started, this, &AMyCharacter::InventoryKey);
	}
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (ui && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
	{
		if (!BackMoving && !DashMoving)
		{
			PlayerHp -= DamageAmount;
			UDamageShowing* da = Cast<UDamageShowing>(Damagesh->GetWidget());
			da->SetVisibility(ESlateVisibility::Visible);
			da->SetDamag(DamageAmount);
			GetWorld()->GetTimerManager().ClearTimer(TimerShowing);
			GetWorld()->GetTimerManager().SetTimer(TimerShowing, FTimerDelegate::CreateLambda([this, da]() {da->SetVisibility(ESlateVisibility::Collapsed); }), 0.5f, false);
		}
		else
		{
			PlayerHp -= 0;
			UE_LOG(LogMypro, Warning, TEXT("PHP:%f"), PlayerHp);
		}
		float HpTemp = (PlayerHp / PlayerHp_Const) * 100;
		UE_LOG(LogMypro, Warning, TEXT("pHp:%f"), HpTemp);
		HP = HpTemp / 100;
		UE_LOG(LogMypro, Warning, TEXT("PMP:%f"), HP);
		ui->OnDamage_P.Broadcast(HP);
		if (HP <= KINDA_SMALL_NUMBER)
		{

			GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetCusorVisual(UIORNOT::UI);
			ui->TypingStart();
		}
	}
	else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp
		|| GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
	{
		if (!BackMoving && !DashMoving)
		{
			if (PlayerController && PlayerController->IsLocalController() && HasAuthority())
			{
				AMyPlayerState* PS = GetPlayerState<AMyPlayerState>();
				if (PS)
				{
					PS->PlayerHPtotal_H -= DamageAmount;
					float HpTemp = (PS->PlayerHPtotal_H / PS->PlayerHPtotalconst_H) * 100;
					HP = HpTemp / 100;
					PS->PlayerHP_H = HP;
				}
			}
			else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
			{
				PlayerController->Sever_SendtheClientHP(DamageAmount);
				PlayerHp -= DamageAmount;
				float HpTemp = (PlayerHp / PlayerHp_Const) * 100;
				HP = HpTemp / 100;
			}
		}
	}
	return  DamageAmount;
}
void AMyCharacter::EndDash()
{
	UCharacterMovementComponent* Move = GetCharacterMovement();
	Move->bUseSeparateBrakingFriction = false;
	Move->GroundFriction = SavedGroundFriction;
	Move->BrakingFriction = SavedBrakingFriction;
	Move->BrakingDecelerationWalking = SavedBrakingDecel;
	Move->StopMovementImmediately();
	if(BackMoving)
	BackMoving =false;
	if (DashMoving)
		DashMoving = false;
	CurrentVelocity = FVector::ZeroVector;
}
void AMyCharacter::MoveKey(const FInputActionValue& Value)
{
	if (!BackMoving&& !DashMoving && !DashMoving && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetCusorVisual() == UIORNOT::UINot)
	{
		SetReplicateMovement(true);
		FVector Diret = Value.Get<FVector>();

		AddMovementInput(GetActorForwardVector(),  Diret.X);
		AddMovementInput(GetActorRightVector(), Diret.Y);
		IsMoving = true;
		float ro = 0.0f;
		if (Diret.X > 0.f)
		{
			AnimInstance->SetDir(0.f);
			ro = -90.0f;
			GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));
			if (Diret.Y > 0.f)
			{
				ro = -45.0f;
				GetMesh()->SetRelativeRotation(FRotator(0, -45.0f, 0));
				AnimInstance->SetDir(45.f);
			}

			else if (Diret.Y < 0.f)
			{
				ro = -135.0f;
				GetMesh()->SetRelativeRotation(FRotator(0, -135.0f, 0));
				AnimInstance->SetDir(-45.f);
			}
		}

		else if (Diret.X < 0.f)
		{
			ro = -270.0f;
			AnimInstance->SetDir(180.f);
			GetMesh()->SetRelativeRotation(FRotator(0, -270.0f, 0));
			if (Diret.Y > 0.f)
			{
				ro = -315.0f;
				GetMesh()->SetRelativeRotation(FRotator(0, -315.0f, 0));
				AnimInstance->SetDir(135.f);
			}

			else if (Diret.Y < 0.f)
			{
				ro = -225.0f;
				GetMesh()->SetRelativeRotation(FRotator(0, -225.0f, 0));
				AnimInstance->SetDir(-135.f);
			}
		}

		else
		{
			if (Diret.Y > 0.f)
			{
				ro = 0.0f;
				GetMesh()->SetRelativeRotation(FRotator(0, 0.0f, 0));
			}

			else if (Diret.Y < 0.f)
			{
				ro = -180.0f;
				GetMesh()->SetRelativeRotation(FRotator(0, -180.0f, 0));
			}
		}
		CurrentVelocity = GetVelocity().GetSafeNormal();
		if (HasAuthority())
		{
			AMyPlayerState* PS = GetPlayerState<AMyPlayerState>();
			if (PS)
			{
				PS->CurrentVelocity_H = CurrentVelocity;
				UE_LOG(LogMypro, Warning, TEXT("CURRENTVECTOR_h : %s"), *CurrentVelocity.ToString());
				PS->MeshPitch_H = ro;
			}
		}
		else
		{
			if (PlayerController)
			{
				PlayerController->Server_SendtheVelocity(CurrentVelocity);
				UE_LOG(LogMypro, Warning, TEXT("CURRENTVECTOR_c : %s"), *CurrentVelocity.ToString());
				PlayerController->Sever_SendtheClientMeshPitch(ro);
			}
		}
	}
}
void AMyCharacter::MoveStop(const FInputActionValue& Value)
{
	IsMoving = false;
}
void AMyCharacter::CameraRotation(const FInputActionValue& Value)
{
	FVector Diret = Value.Get<FVector>();
	if (CameraRo)
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
	CameraRo = true;
}

void AMyCharacter::CameraRotation_Cancel(const FInputActionValue& Value)
{
	LookAt = true;
	CameraRo = false;
	Camera->SetRelativeRotation(FRotator(30, 0, 0));
}

void AMyCharacter::BackKey(const FInputActionValue& Value)
{
	if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
		BackDash(CurrentVelocity);
	else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp
		|| GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
	{
		if (HasAuthority())
			Multicast_Back(CurrentVelocity);
		else
			Server_Back(CurrentVelocity);
	}
}
void AMyCharacter::DashKey(const FInputActionValue& Value)
{
	if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
		Dash(CurrentVelocity);
	else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp
		|| GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::Party)
	{
		if (HasAuthority())
			Multicast_Dash(CurrentVelocity);
		else
			Server_Dash(CurrentVelocity);
	}
}
void AMyCharacter::InventoryKey(const FInputActionValue& Value)
{
	if (!BackMoving && !DashMoving)
	{	
		ui->GetInventory()->SetVisibility(ESlateVisibility::Visible);
		GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetCusorVisual(UIORNOT::UI);
	}
}
void AMyCharacter::AttackKey(const FInputActionValue& Value)
{
	if (AnimInstance&&!IsMoving&&!BackMoving && !DashMoving&& GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetCusorVisual() ==UIORNOT::UINot)
		AnimInstance->PlayAttack();
}

void AMyCharacter::Skill1Key(const FInputActionValue& Value)
{
	if (AnimInstance && !IsMoving && !BackMoving && Canskill1 && !DashMoving && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetCusorVisual() == UIORNOT::UINot)
		AnimInstance->PlaySkill(0);
}

void AMyCharacter::Skill2Key(const FInputActionValue& Value)
{
	if (AnimInstance && !IsMoving && !BackMoving && Canskill2 && !DashMoving && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetCusorVisual() == UIORNOT::UINot)
		AnimInstance->PlaySkill(1);
}

void AMyCharacter::Skill3Key(const FInputActionValue& Value)
{
	if (AnimInstance && !IsMoving && !BackMoving&& Canskill3 && !DashMoving && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetCusorVisual() == UIORNOT::UINot)
		AnimInstance->PlaySkill(2);
}

void AMyCharacter::Skill4Key(const FInputActionValue& Value)
{
	if (AnimInstance && !IsMoving && !BackMoving && Canskill4 && !DashMoving && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetCusorVisual() == UIORNOT::UINot)
		AnimInstance->PlaySkill(3);
}
void AMyCharacter::Skill1coolTime(float speed)
{
	Canskill1 = false;
	Skill1cool = 1.0F;
	Skill1Speed = speed;
}
void AMyCharacter::Skill2coolTime(float speed)
{
	Canskill2 = false;
	Skill2cool = 1.0F;
	Skill2Speed = speed;
}
void AMyCharacter::Skill3coolTime(float speed)
{
	Canskill3 = false;
	Skill3cool = 1.0F;
	Skill3Speed = speed;
}
void AMyCharacter::Skill4coolTime(float speed)
{
	Canskill4 = false;
	Skill4cool = 1.0F;
	Skill4Speed = speed;
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
void AMyCharacter::MpbarSync(float cost)
{
	PlayerMp -= cost;
	UE_LOG(LogMypro, Warning, TEXT("PMP:%f"), PlayerMp);
	float mpTemp = (PlayerMp / PlayerMp_Const) * 100;
	UE_LOG(LogMypro, Warning, TEXT("pmp:%f"), mpTemp);
	MP = mpTemp / 100;
	UE_LOG(LogMypro, Warning, TEXT("PMP:%f"), MP);
	if (ui && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
	ui->OnSyncMp_P.Broadcast(MP);
	else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
	{
		if (PlayerController && PlayerController->IsLocalController()&&HasAuthority())
		{
			AMyPlayerState* PS = GetPlayerState<AMyPlayerState>();
			if (PS)
				PS->PlayerMP_H = MP;
		}
		else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
			PlayerController->Sever_SendtheClientMP(MP);
	}
}
void AMyCharacter::AddMpbar(float cost)
{
  PlayerMp = PlayerMp < PlayerMp_Const? PlayerMp + cost: PlayerMp_Const;
  float mpTemp = (PlayerMp / PlayerMp_Const) * 100;
  UE_LOG(LogMypro, Warning, TEXT("addpmp:%f"), mpTemp);
  MP = mpTemp / 100;
  UE_LOG(LogMypro, Warning, TEXT("addPMP:%f"), MP);
  if (ui && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::playgame)
  ui->OnSyncMp_P.Broadcast(MP);
  else if (GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetGameState() == NowGameState::pvp)
  { 
	 
	  if (PlayerController && PlayerController->IsLocalController()&&HasAuthority())
	  {
		  AMyPlayerState* PS = GetPlayerState<AMyPlayerState>();
		  if (PS)
			  PS->PlayerMP_H = MP;
	  }
	  else if (PlayerController && PlayerController->IsLocalController() && !HasAuthority())
		  PlayerController->Sever_SendtheClientMP(MP);
  }
}
void AMyCharacter::SendtheMontageAttack(bool up, int32 index)
{
	if (HasAuthority())
		Multicast_PlayMontageAttack(up, index);
	else
		Server_PlayMontageAttack(up, index);
}

void AMyCharacter::SendtheMontageSkill(int32 index)
{
	if (HasAuthority())
		Multicast_PlayMontageSkill(index);
	else
		Server_PlayMontageSkill(index);
}
void AMyCharacter::Dash(FVector velocity)
{
	if (!BackMoving && !DashMoving && !DashMoving && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetCusorVisual() == UIORNOT::UINot)
	{
		UCharacterMovementComponent* Move = GetCharacterMovement();
		Move->bUseSeparateBrakingFriction = true;
		Move->GroundFriction = 0.5f;
		Move->BrakingFriction = 0.5f;
		Move->BrakingDecelerationWalking = 250.f;
		FVector	NewLocation = velocity * 1500.0f;
		LaunchCharacter(NewLocation, true, false);
		DashMoving = true;
		BackMoving = true;
		GetWorldTimerManager().ClearTimer(DashTimer);
		GetWorld()->GetTimerManager().SetTimer(DashTimer, this, &AMyCharacter::EndDash, 1.0, false);
		if (AnimInstance)
			AnimInstance->PlayBack();
	}
}
void AMyCharacter::BackDash(FVector velocity)
{
	if (!BackMoving && !DashMoving && !DashMoving && GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetCusorVisual() == UIORNOT::UINot)
	{
		UCharacterMovementComponent* Move = GetCharacterMovement();
		Move->bUseSeparateBrakingFriction = true;
		Move->GroundFriction = 0.5f;
		Move->BrakingFriction = 0.5f;
		Move->BrakingDecelerationWalking = 250.f;
		FVector	NewLocation= -velocity * 1500.0f;
		LaunchCharacter(NewLocation, true, false);
		BackMoving = true;
		DashMoving = true;
		GetWorldTimerManager().ClearTimer(DashTimer);
		GetWorld()->GetTimerManager().SetTimer(DashTimer, this, &AMyCharacter::EndDash, 1.0, false);
		if (AnimInstance)
			AnimInstance->PlayBack();
	}
}
void AMyCharacter::Multicast_PlayMontageAttack_Implementation(bool up, int32 index)
{
	if (AnimInstance)
	{
		AnimInstance->PlayAttack_interanl(up, index);
		UE_LOG(LogMypro, Warning, TEXT("attackindex : %d"), index);
	}
}

void AMyCharacter::Multicast_PlayMontageSkill_Implementation(int32 index)
{
	if (AnimInstance)
	{
		AnimInstance->PlaySkill_interanl(index);
		UE_LOG(LogMypro, Warning, TEXT("skillindex : %d"), index);
	}
}
void AMyCharacter::Server_PlayMontageAttack_Implementation(bool up, int32 index)
{
	Multicast_PlayMontageAttack(up, index);
}

void AMyCharacter::Server_PlayMontageSkill_Implementation(int32 index)
{
	Multicast_PlayMontageSkill(index);
}
void AMyCharacter::Multicast_NullOverlap_Implementation()
{
	GetMesh()->SetOverlayMaterial(nullptr);
	Niagara->SetVisibility(false);
}

void AMyCharacter::Server_NullOverlap_Implementation()
{
	Multicast_NullOverlap();
}

void AMyCharacter::Server_Dash_Implementation(FVector velocity)
{
	Multicast_Dash(velocity);
}

void AMyCharacter::Server_Back_Implementation(FVector velocity)
{
	Multicast_Back(velocity);
}

void AMyCharacter::Multicast_Dash_Implementation(FVector velocity)
{
	Dash(velocity);
}

void AMyCharacter::Multicast_Back_Implementation(FVector velocity)
{
	BackDash(velocity);
}
