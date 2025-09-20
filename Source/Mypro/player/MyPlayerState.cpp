// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include "MainPlayerController.h"

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AMyPlayerState, MyCharacter_H);
    DOREPLIFETIME(AMyPlayerState, MyCharacter_C);
    DOREPLIFETIME(AMyPlayerState, Inventoryco);
    DOREPLIFETIME(AMyPlayerState, Ready_H);
    DOREPLIFETIME(AMyPlayerState, Ready_C);
    DOREPLIFETIME(AMyPlayerState, Pitch_H);
    DOREPLIFETIME(AMyPlayerState, Pitch_C);
    DOREPLIFETIME(AMyPlayerState, MeshPitch_C);
    DOREPLIFETIME(AMyPlayerState, MeshPitch_H);
    DOREPLIFETIME(AMyPlayerState, PlayerHP_H);
    DOREPLIFETIME(AMyPlayerState, PlayerMP_H);
    DOREPLIFETIME(AMyPlayerState, PlayerHP_C);
    DOREPLIFETIME(AMyPlayerState, PlayerMP_C);
    DOREPLIFETIME(AMyPlayerState, PlayerHPtotal_C);
    DOREPLIFETIME(AMyPlayerState, PlayerHPtotal_H);
    DOREPLIFETIME(AMyPlayerState, PlayerHPtotalconst_C);
    DOREPLIFETIME(AMyPlayerState, PlayerHPtotalconst_H);
    DOREPLIFETIME(AMyPlayerState, CurrentVelocity_H);
    DOREPLIFETIME(AMyPlayerState, CurrentVelocity_C);
}
void AMyPlayerState::BeginPlay()
{
    Super::BeginPlay();
    AMainPlayerController* pc = Cast<AMainPlayerController>(GetOwner());
    if (pc)
    {
        if (pc->HasAuthority())
        {
            MyCharacter_H = GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSelectedcharacter();
            MyCharacter_C = GetWorld()->GetGameInstance()->GetSubsystem<UGameManager>()->GetSelectedcharacter_client();
        }
    }
}
AMyPlayerState::AMyPlayerState()
{
    Inventoryco = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inve"));
    SetReplicates(true);
}

void AMyPlayerState::CopyProperties(APlayerState* NewPlayerState)
{
    Super::CopyProperties(NewPlayerState);
    AMyPlayerState* state  =Cast<AMyPlayerState>(NewPlayerState);
    if (state)
    {
        state->MyCharacter_C = MyCharacter_C;
    }
}




