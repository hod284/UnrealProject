// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../singleton/GameManager.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 gamesubinstance ->gameinstance  ->levelload -> gamemode ->playercontroller ->charactercontroller
 */
UCLASS()
class MYPRO_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	AMainPlayerController();
	virtual void Tick(float DeltaTime) override;
public:
	UFUNCTION(Server, Reliable)
	void Server_SetSelectedPawn(Characters CH);
	UFUNCTION(Server, Reliable)
	void Sever_SendtheRotate(float Pi_h);
	UFUNCTION(Server, Reliable)
	void Sever_GettheRotate();
	UFUNCTION(Client, Reliable)
	void Client_GettheRotate(float Pi_h, float Pi_c);
	UFUNCTION(Server, Reliable)
	void Sever_SendtheReady(bool ready);
	UFUNCTION(Server, Reliable)
	void Sever_GettheReady();
	UFUNCTION(Client, Reliable)
	void Client_GettheReady(bool ready_h, bool ready_c);
	UFUNCTION(Server, Reliable)
	void Sever_GettheSelectCharacter();
	UFUNCTION(Client, Reliable)
	void Client_GettheSelectCharacter(Characters ch_c, Characters ch_h);
	UFUNCTION(Server, Reliable)
	void Sever_GettheMPandHP();
	UFUNCTION(Client, Reliable)
	void Client_GettheMPandHP(float Hp_H,float Mp_H, float Hp_C, float Mp_C);
	UFUNCTION(Server, Reliable)
	void Sever_SendtheClientHP(float Hp);
	UFUNCTION(Server, Reliable)
	void Sever_SendtheClientMP(float Mp);

	TSubclassOf<APawn> GetSelectCharactertClass();
	float  Pitch_c;
	float	Pitch_h;
	bool  Ready_c;
	bool  Ready_h;
	float PlayerHP_H=1.0;
	float PlayerMP_H=1.0;
	float PlayerHP_C=1.0;
	float PlayerMP_C=1.0;
	Characters MyCharacter_C = Characters::None;
	Characters MyCharacter_H = Characters::None;
};
