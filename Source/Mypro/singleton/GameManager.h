// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManager.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UGameManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
private:
	// ���� �޴������� ���� ������Ʈ ����
	NowGameState  state = NowGameState ::None;
	// ���� �޴������� �÷��� ĳ���� ����
	CharacterChoice character = CharacterChoice::None;
public:
	// �⺻ ������
	// �����ڿ� �ʱ�ȭ���� �ʰڴٴ¶�
	UGameManager() =default;

	void SetGameState(NowGameState newState) {
		state = newState; 
	}
	const NowGameState GetGameState() const { 
		return state; 
	}
	void SetSelectCharacter(CharacterChoice  ch) {
		character = ch;
	}
	const CharacterChoice  GetSelectedcharacter() const {
		return character;
	}
};
