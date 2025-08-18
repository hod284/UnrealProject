#pragma once
/*
����� ������ ��������Ʈ�� �ʿ��� ��� ���� �� ��ũ�� ���ռ� �Դϴ�
*/


// ��� ���� ��Ƴ��°�
#include "EngineMinimal.h"
#include "Engine.h"
#include "Engine/EngineTypes.h"
#include "Engine/GameViewportClient.h"
//
// ���� ���� ��� ���� ��Ƴ���	��
#include "Net/UnrealNetwork.h"
#include "Engine/AssetManager.h"


//
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "MediaPlayer.h"
#include "MediaSoundComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "LevelSequence.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/LevelStreaming.h"
#include "Streaming/LevelStreamingDelegates.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
// �̹��� ������� ��Ƴ�����
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
//������	��� ���� ��Ƴ�����
#include "Camera/CameraComponent.h"
#include "Gameinfo.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogMypro, Warning, All);

// Team : 0 ~ 255 ������ ��
#define	TeamNeutral	255
#define	TeamMonster	30
#define	TeamPlayer	1
/*
  �̳� Ŭ������ �̳��� ������
  �̳��� �� �̳�Ŭ������ �������� ������������ �ڽ��� �ڽĿ� �������� �δ³��� ���̿� Ÿ���� �������� ������ �ִ�
  �̳��� �ڵ����� int�� ���ϴ� �ݸ� �̳� Ŭ������ �����ڰ� �����־���� Ÿ���� �����ȴ�
  �������� ������ �ٸ��� ���� �̳��� �ߺ��� ������ �ȵǴ� �ݸ� �̳� Ŭ������ �ߺ��� ����� �ȴ�
*/
//���ӻ��� ����
UENUM()
enum class  NowGameState: uint8
{
	None,Intro, playgame, gameover
};

//����UI ���� �ƴ��� ����
UENUM(BlueprintType)
enum class UIORNOT : uint8
{
	UI, UINot
};

//����ĳ���� ����
UENUM(BlueprintType)
enum class Characters : uint8
{
	Guiden, Warrior,DarkMagion, None
};
// ���� ���̾� ����
UENUM(BlueprintType)
enum class ObjestLayer : uint8
{
	wall,floor,light
};
// ���� ������ ����ü ����	
USTRUCT(BlueprintType)
struct FCharacterInfo:public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	Characters CType; // ĳ���� Ÿ��
	UPROPERTY(EditAnywhere)
	int32 HP; // ü��
	UPROPERTY(EditAnywhere)
	int32 MP; // ����
	UPROPERTY(EditAnywhere)
	int32 ATK; // ���ݷ�
	UPROPERTY(EditAnywhere)
	int32 Skill1_ATK; // ��ų1 ���ݷ� 
	UPROPERTY(EditAnywhere)
	int32 Skill2_ATK; // ��ų2 ���ݷ� 
	UPROPERTY(EditAnywhere)
	int32 Skill3_ATK; // ��ų3 ���ݷ� 
	UPROPERTY(EditAnywhere)
	int32 Skill4_ATK; // ��ų4 ���ݷ� 
};
USTRUCT(BlueprintType)
struct FCMonsterInfo :public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	int32 HP; // ü��
	UPROPERTY(EditAnywhere)
	int32 StunGage; // ���ϰ�����
	UPROPERTY(EditAnywhere)
	int32 ATK; // ���ݷ�
	UPROPERTY(EditAnywhere)
	int32 Skill1_ATK; // ��ų1 ���ݷ� 
	UPROPERTY(EditAnywhere)
	int32 Skill2_ATK; // ��ų2 ���ݷ� 
	UPROPERTY(EditAnywhere)
	int32 Skill3_ATK; // ��ų3 ���ݷ� 
	UPROPERTY(EditAnywhere)
	int32 Skill4_ATK; // ��ų4 ���ݷ� 
};
USTRUCT(BlueprintType)
struct FPlayerAnimInfo : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TMap<FName, TObjectPtr<UBlendSpace>>	BlendSpaceMap;

	UPROPERTY(EditAnywhere)
	TMap<FName, TObjectPtr<UAnimMontage>>	MontageMap;

	UPROPERTY(EditAnywhere)
	TArray<FName>							AttackSectionArray;
	UPROPERTY(EditAnywhere)
	TArray<FName>							SkillSectionArray;
};
USTRUCT(BlueprintType)
struct FMonsterAnimInfo : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TMap<FName, TObjectPtr<UAnimSequence>>	SequenceMap;
	UPROPERTY(EditAnywhere)
	TMap<FName, TObjectPtr<UAnimMontage>>	MontageMap;
};
UENUM(BlueprintType)
enum class EMonsterDefaultAnim : uint8
{
	Idle,
	Stun,
	Attack1,
	Attack2,
	Attack3,
	Attack4,
	Death
};