#pragma once
/*
이헤더 파일은 이프로젝트에 필요한 헤더 파일 및 메크로 집합소 입니다
*/


// 헤더 파일 모아놓는곳
#include "EngineMinimal.h"
#include "Engine.h"
#include "Engine/EngineTypes.h"
//
// 리슨 서버 헤더 파일 모아놓은	곳
#include "Net/UnrealNetwork.h"



//
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"

// 이미지 헤더파일 모아놓은곳
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "Components/ListView.h"
#include "Components/TileView.h"
#include "Components/TreeView.h"
#include "Components/Border.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
//
//나머지	헤더 파일 모아놓은곳
#include "Camera/CameraComponent.h"
#include "Gameinfo.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogMypro, Warning, All);


/*
  이넘 클래스와 이넘의 차이점
  이넘은 과 이넘클래스의 차이점은 전역스코프와 자신의 자식에 스코프를 두는냐의 차이와 타입을 안전성을 따질수 있다
  이넘은 자동으로 int로 변하는 반면 이넘 클래스는 개발자가 정해주어야지 타입이 지정된다
  스코프의 개념이 다르다 보니 이넘은 중복이 인정이 안되는 반면 이넘 클래스는 중복이 허용이 된다
*/
//게임상태 정의
UENUM()
enum class  NowGameState: uint8
{
	None,Intro, playgame, gameover
};

//게임UI 인지 아니지 여부
UENUM(BlueprintType)
enum class UIORNOT : uint8
{
	UI, UINot
};

//게임캐릭터 정의
UENUM(BlueprintType)
enum class Characters : uint8
{
	Guiden, Warrior,DarkMagion, None
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
	Characters CType; // 캐릭터 타입
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