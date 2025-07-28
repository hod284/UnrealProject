#pragma once
/*
����� ������ ��������Ʈ�� �ʿ��� ��� ���� �� ��ũ�� ���ռ� �Դϴ�
*/


// ��� ���� ��Ƴ��°�
#include "EngineMinimal.h"
#include "Engine.h"
#include "Engine/EngineTypes.h"
#include "../Mypro/common/PointerManager.h"
#include "Gameinfo.generated.h"
// �����ͳ� �𸮾� ����Ʈ ������ ��� ���� Ŭ����
extern TObjectPtr<PointerManager> UpointerManager;

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
