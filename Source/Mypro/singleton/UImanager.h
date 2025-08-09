// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../Widget/PlayMainUI.h"
#include "../Widget/IntroMainUI.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UImanager.generated.h"

/**
 메인 위젯들을 관리하는 싱글톤 클래스입니다.
 */
UCLASS()
class MYPRO_API UUImanager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TSubclassOf<UPlayMainUI> PlayMainUI; // 플레이 메인클래스
	UPROPERTY()
	TSubclassOf<UIntroMainUI> IntroMainUI; // 인트로 메인 클래스
	UPROPERTY()
    TObjectPtr <UUserWidget> PlayMainUI_widget; // 플레이 메인 위젯
	UPROPERTY()
	TObjectPtr<UUserWidget> IntroMainUI_widget; // 인트로 메인 위젯
	// 첫번쩨씬에서 쓰일 메인 위젯 get
	// tobject ptr 앞에 쓰이는 const는 반환값을 수정할수 없다는 의미입니다.
	// GetPlayMainUI_widget() = PlayMainUI_widget; // 이렇게 쓰면 안됩니다.
	// tobject ptr 뒤에 쓰이는 const는 멤버변수을 수정할수 없다는 의미입니다.
	// const TObjectPtr<UUserWidget> GetPlayMainUI_widget() const
	//{
	//	PlayMainUI_widget = IntroMainUI_widget; 멤버변수를 수정할수 없으므로 에러가 납니다
	//	return PlayMainUI_widget;
	//}
	const TObjectPtr<UUserWidget> GetPlayMainUI_widget() const
	{
		
		return PlayMainUI_widget;
	}
	// 플레이씬에서 쓰일 메인 위젯 get
	const TObjectPtr<UUserWidget> GetIntroMainUI_widget() const
	{
		return IntroMainUI_widget;
	}


	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UUImanager();
};
