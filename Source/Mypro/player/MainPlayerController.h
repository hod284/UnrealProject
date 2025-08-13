// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../singleton/GameManager.h"
#include "../singleton/UImanager.h"
#include "../common/IntroSceneObject.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 클라이언트 플레이어 컨트롤러 클래스입니다.
 여기서 인트로 위젯클래스를 뷰포트에 추가하는 이유는 서버와 통신없이 클라이언트만 보이게 하기 위합입니다
 게임모드는 서버와 통신을 하기 때문에 서버와 통신이 일어나면 인트로 위젯이 클라이언트쪽에 안보이게 될수 있어서 여기에 인트로 위젯을 생성및 뷰포트에 추가합니다
 케릭터 컨트롤러 생성순서
 gameinstance ->gamesubinstance ->levelload -> gamemode ->playercontroller ->charactercontroller
 */
UCLASS()
class MYPRO_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	// override는 부모클래스의 함수를 재정의한다고 컴파일러에게 명확히 알려준다.
	virtual void BeginPlay() override;
	TArray<AActor*>SceneActorList;
	AMainPlayerController();
public:
    /// <summary>
    /// 레벨에 있는 인트로씬 옵브젝트 찾기위해 만든 함수
    /// </summary>
    /// <returns></returns>
    AActor* GetLevelSceneObjectActor() const
    {
		/*
		getclass와staticclass의 차이점은 파생클래스를 가져오는냐 아니면 자신의 클래스를 가져오는냐의 차이
		getlass는 파생클래스까지 가져오고 staticclass는 자신의 클래스만 가져온다
		그래서 두개를 이용해 특정 클래스 액터를 찾아오는 로직 생성
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
	// 캐릭터 선택한 클래스 정보를 반환하는 함수입니다.
	TSubclassOf<APawn> GetSelectCharactertClass();
	
};
