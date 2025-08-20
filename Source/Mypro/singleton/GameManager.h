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
	// 게임 메니저에서 게임 스테이트 설정
	NowGameState  state = NowGameState ::None;
	// 게임 메니저에서 플레이 캐릭터 선택
	Characters character = Characters::None;
public:
	// 기본 생성자
	// 생성자에 초기화하지 않겠다는뜻
	UGameManager() =default;
	// TSubclassOf 는 참조타입을 나타내는 언리얼 엔진의 템플릿 클래스입니다.
	// 메모리 할당과 다른거임
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
