// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AMyPlayerState, MyCharacter);
    DOREPLIFETIME(AMyPlayerState, Inventoryco);
    DOREPLIFETIME(AMyPlayerState, SelectCharacter);
    DOREPLIFETIME(AMyPlayerState, ReadyCount);
    DOREPLIFETIME(AMyPlayerState, Pitch_H);
    DOREPLIFETIME(AMyPlayerState, Pitch_C);
}

AMyPlayerState::AMyPlayerState()
{
    Inventoryco = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inve"));
    SetReplicates(true);
}




