#pragma once
/*
����� ������ ��������Ʈ�� �ʿ��� ��� ���� �� ��ũ�� ���ռ� �Դϴ�
*/


// ��� ���� ��Ƴ��°�
#include "EngineMinimal.h"
#include "Engine.h"
#include "Engine/EngineTypes.h"
//


// �̹��� ������� ��Ƴ�����
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ListView.h"
#include "Components/TileView.h"
#include "Components/TreeView.h"
#include "Components/Border.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
//

#include "Gameinfo.generated.h"



//���ӻ��� ����
UENUM()
enum  NowState: uint8
{
	Intro, playgame, gameover
};

//���ӻ��� ����
UENUM(BlueprintType)
enum class CharacterChoice : uint8
{
	Guiden, Warrior,DarkMagion
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
	CharacterChoice CType; // ĳ���� Ÿ��
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

// �𸮾� �α� ���� 
DECLARE_LOG_CATEGORY_EXTERN(LogMypro, Log, All);
