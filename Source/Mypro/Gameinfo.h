#pragma once
/*
����� ������ ��������Ʈ�� �ʿ��� ��� ���� �� ��ũ�� ���ռ� �Դϴ�
*/


// ��� ���� ��Ƴ��°�
#include "EngineMinimal.h"
#include "Engine.h"
#include "Engine/EngineTypes.h"
//
// ���� ���� ��� ���� ��Ƴ���	��
#include "Net/UnrealNetwork.h"



//
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"

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