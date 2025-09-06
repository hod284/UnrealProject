// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../singleton/GameManager.h"
#include "../singleton/UImanager.h"
#include "../common/IntroSceneObject.h"
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
	
protected:
	// override�� �θ�Ŭ������ �Լ��� �������Ѵٰ� �����Ϸ����� ��Ȯ�� �˷��ش�.
	virtual void BeginPlay() override;
	TArray<AActor*>SceneActorList;
	AMainPlayerController();
	virtual void Tick(float DeltaTime) override;
public:
    /// <summary>
    /// ������ �ִ� ��Ʈ�ξ� �ɺ���Ʈ ã������ ���� �Լ�
    /// </summary>
    /// <returns></returns>
    AActor* GetLevelSceneObjectActor() const
    {
		/*
		getclass��staticclass�� �������� �Ļ�Ŭ������ �������³� �ƴϸ� �ڽ��� Ŭ������ �������³��� ����
		getlass�� �Ļ�Ŭ�������� �������� staticclass�� �ڽ��� Ŭ������ �����´�
		�׷��� �ΰ��� �̿��� Ư�� Ŭ���� ���͸� ã�ƿ��� ���� ����
		*/
	   AActor* Choice  = nullptr;
	   for (AActor* Actor : SceneActorList)
	   {
	      	if (Actor->GetClass() == AIntroSceneObject :: StaticClass())
	      	{
	      		Choice = Actor;
				break;
			}
	   }
	   return Choice;
    }
	
	// ĳ���� ������ Ŭ���� ������ ��ȯ�ϴ� �Լ��Դϴ�.
	TSubclassOf<APawn> GetSelectCharactertClass();
	
};
