#pragma once
/*
이헤더 파일은 이프로젝트에 필요한 헤더 파일 및 메크로 집합소 입니다
*/


// 헤더 파일 모아놓는곳
#include "EngineMinimal.h"
#include "Engine.h"
#include "Engine/EngineTypes.h"
#include "../Mypro/common/PointerManager.h"
#include "Gameinfo.generated.h"
// 포인터나 언리얼 스마트 포인터 모아 놓은 클래스
extern TObjectPtr<PointerManager> UpointerManager;

//게임상태 정의
UENUM()
enum  NowState: uint8
{
	Intro, playgame, gameover
};

//게임상태 정의
UENUM(BlueprintType)
enum class CharacterChoice : uint8
{
	Guiden, Warrior,DarkMagion
};
// 게임 레이어 정의
UENUM(BlueprintType)
enum class ObjestLayer : uint8
{
	wall,floor,light
};
// 게임 데이터 구조체 정의	
USTRUCT(BlueprintType)
struct FCharacterInfo:public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	CharacterChoice CType; // 캐릭터 타입
	UPROPERTY(EditAnywhere)
	int32 HP; // 체력
	UPROPERTY(EditAnywhere)
	int32 MP; // 마나
	UPROPERTY(EditAnywhere)
	int32 ATK; // 공격력
	UPROPERTY(EditAnywhere)
	int32 Skill1_ATK; // 스킬1 공격력 
	UPROPERTY(EditAnywhere)
	int32 Skill2_ATK; // 스킬2 공격력 
	UPROPERTY(EditAnywhere)
	int32 Skill3_ATK; // 스킬3 공격력 
	UPROPERTY(EditAnywhere)
	int32 Skill4_ATK; // 스킬4 공격력 
};

// 언리얼 로그 정의 
DECLARE_LOG_CATEGORY_EXTERN(LogMypro, Log, All);
