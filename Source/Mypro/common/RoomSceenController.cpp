// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomSceenController.h"

// Sets default values
ARoomSceenController::ARoomSceenController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoomSceenController::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->SetCusorVisual(UIORNOT::UI);
	URoomWidgetClass* ui = Cast<URoomWidgetClass>(GetWorld()->GetGameInstance()->GetSubsystem<UUImanager>()->GetRoom_widget());
	ui->AddToViewport();
	AMainPlayerController* PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	PC->SetViewTarget(Camera);
}

void ARoomSceenController::GettheValue()
{
	AMainPlayerController* PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PC->HasAuthority())
	{
		AMyPlayerState* PS = Cast<AMyPlayerState>(PC->GetPlayerState<AMyPlayerState>());
		Pitch_h = PS->Pitch_H;
		UE_LOG(LogMypro, Warning, TEXT("H%f"), PS->Pitch_H);
		Pitch_c = PS->Pitch_C;
		UE_LOG(LogMypro, Warning, TEXT("H%f"), PS->Pitch_C);
	}
	else
	{

		PC->Sever_GettheRotate();
		Pitch_h = PC->Pitch_h;
		UE_LOG(LogMypro, Warning, TEXT("C%f"), PC->Pitch_h);
		Pitch_c = PC->Pitch_c;
		UE_LOG(LogMypro, Warning, TEXT("C%f"), PC->Pitch_c);
	}
	
}

// Called every frame
void ARoomSceenController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GettheValue();
	FRotator Ro1 = FMath::RInterpTo(SP1->GetActorRotation(), FRotator(0,Pitch_h,0), 0.2, 0.5);
	SP1->SetActorRotation(Ro1);
	FRotator Ro2 = FMath::RInterpTo(SP2->GetActorRotation(), FRotator(0,Pitch_c , 0), 0.2, 0.5);
	SP2->SetActorRotation(Ro2);
}




