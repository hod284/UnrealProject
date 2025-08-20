// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../common/PlaySceneObject.h"
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
	Characters character = Characters::None;
public:
	// �⺻ ������
	// �����ڿ� �ʱ�ȭ���� �ʰڴٴ¶�
	UGameManager() =default;
	// TSubclassOf �� ����Ÿ���� ��Ÿ���� �𸮾� ������ ���ø� Ŭ�����Դϴ�.
	// �޸� �Ҵ�� �ٸ�����
	APlaySceneObject* GetPlayerLevelObject()
	{
        APlaySceneObject* ob =Cast<APlaySceneObject>( UGameplayStatics::GetActorOfClass(GetWorld(), APlaySceneObject::StaticClass()));
		if (ob == nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("Player character not found."));
		}
		return ob;
	}
	void SetGameState(NowGameState newState) {
		state = newState; 
	}
	const NowGameState GetGameState() const { 
		return state; 
	}
	void SetSelectCharacter(Characters  ch) {
		character = ch;
	}
	const Characters  GetSelectedcharacter() const {
		return character;
	}
};
