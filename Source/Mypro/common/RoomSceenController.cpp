// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomSceenController.h"
#include "../player/SelectCharacter.h"
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
		Pitch_H = PS->Pitch_H;
		Pitch_C = PS->Pitch_C;
		ReadyOntheNIagara_C = PS->Ready_C;
		ReadyOntheNIagara_H = PS->Ready_H;
	}
	else
	{
		PC->Sever_GettheReady();
		PC->Sever_GettheRotate();
		Pitch_H = PC->Pitch_h;
		Pitch_C = PC->Pitch_c;
		ReadyOntheNIagara_C = PC->Ready_c;
		ReadyOntheNIagara_H = PC->Ready_h;
	}
	if (ReadyOntheNIagara_H)
	{
		ASelectCharacter* select1 = nullptr;
		int32 r = static_cast<int32>(Pitch_H);
		switch (r)
		{
		case 0:
			select1 = Cast<ASelectCharacter>(SP1_Warrior);
			break;
		case -90:
			select1= Cast<ASelectCharacter>(SP1_Gudien);
			break;
		case -180:
			select1 = Cast<ASelectCharacter>(SP1_DARK);
			break;
		}
		select1->StartGame();
	}
	if (ReadyOntheNIagara_C)
	{
		ASelectCharacter* select2 = nullptr;
		int32 r = static_cast<int32>(Pitch_C);
		switch (r)
		{
		case 0:
			select2= Cast<ASelectCharacter>(SP2_Warrior);
			break;
		case -90:
			select2 = Cast<ASelectCharacter>(SP2_Gudien);
			break;
		case -180:
			select2 = Cast<ASelectCharacter>(SP2_DARK);
			break;
		}
		select2->StartGame();
	}
}

// Called every frame
void ARoomSceenController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GettheValue();
	FRotator Ro1 = FMath::RInterpTo(SP1->GetActorRotation(), FRotator(0,Pitch_H,0), 0.2, 0.5);
	SP1->SetActorRotation(Ro1);
	FRotator Ro2 = FMath::RInterpTo(SP2->GetActorRotation(), FRotator(0,Pitch_C , 0), 0.2, 0.5);
	SP2->SetActorRotation(Ro2);
}




