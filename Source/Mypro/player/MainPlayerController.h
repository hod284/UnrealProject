// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../singleton/GameManager.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 Ŭ���̾�Ʈ �÷��̾� ��Ʈ�ѷ� Ŭ�����Դϴ�.
 ���⼭ ��Ʈ�� ����Ŭ������ ����Ʈ�� �߰��ϴ� ������ ������ ��ž��� Ŭ���̾�Ʈ�� ���̰� �ϱ� �����Դϴ�
 ���Ӹ��� ������ ����� �ϱ� ������ ������ ����� �Ͼ�� ��Ʈ�� ������ Ŭ���̾�Ʈ�ʿ� �Ⱥ��̰� �ɼ� �־ ���⿡ ��Ʈ�� ������ ������ ����Ʈ�� �߰��մϴ�
 �ɸ��� ��Ʈ�ѷ� ��������
 gameinstance ->gamesubinstance ->levelload -> gamemode ->playercontroller ->charactercontroller
 */
UCLASS()
class MYPRO_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	
	TSubclassOf<UUserWidget> MainWidgetBluprinte; // ������ �������� �ɸ��� ���� �������Ʈ�Դϴ�.
	TObjectPtr<UUserWidget> MainWidget; // ������ �������� �ɸ��� �����Դϴ�.
	AMainPlayerController();// ������
	// override�� �θ�Ŭ������ �Լ��� �������Ѵٰ� �����Ϸ����� ��Ȯ�� �˷��ش�.
	virtual void BeginPlay() override;
};
