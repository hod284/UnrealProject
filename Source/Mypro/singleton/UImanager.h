// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../Widget/PlayMainUI.h"
#include "../Widget/IntroMainUI.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UImanager.generated.h"

/**
 ���� �������� �����ϴ� �̱��� Ŭ�����Դϴ�.
 */
UCLASS()
class MYPRO_API UUImanager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TSubclassOf<UPlayMainUI> PlayMainUI; // �÷��� ����Ŭ����
	UPROPERTY()
	TSubclassOf<UIntroMainUI> IntroMainUI; // ��Ʈ�� ���� Ŭ����
	UPROPERTY()
    TObjectPtr <UUserWidget> PlayMainUI_widget; // �÷��� ���� ����
	UPROPERTY()
	TObjectPtr<UUserWidget> IntroMainUI_widget; // ��Ʈ�� ���� ����
	// ù���ž����� ���� ���� ���� get
	// tobject ptr �տ� ���̴� const�� ��ȯ���� �����Ҽ� ���ٴ� �ǹ��Դϴ�.
	// GetPlayMainUI_widget() = PlayMainUI_widget; // �̷��� ���� �ȵ˴ϴ�.
	// tobject ptr �ڿ� ���̴� const�� ��������� �����Ҽ� ���ٴ� �ǹ��Դϴ�.
	// const TObjectPtr<UUserWidget> GetPlayMainUI_widget() const
	//{
	//	PlayMainUI_widget = IntroMainUI_widget; ��������� �����Ҽ� �����Ƿ� ������ ���ϴ�
	//	return PlayMainUI_widget;
	//}
	const TObjectPtr<UUserWidget> GetPlayMainUI_widget() const
	{
		
		return PlayMainUI_widget;
	}
	// �÷��̾����� ���� ���� ���� get
	const TObjectPtr<UUserWidget> GetIntroMainUI_widget() const
	{
		return IntroMainUI_widget;
	}


	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UUImanager();
};
