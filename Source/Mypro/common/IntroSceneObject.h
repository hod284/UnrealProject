// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../player/SelectCharacter.h"
#include "../singleton/UImanager.h"
#include "../singleton/GameManager.h"
#include "GameFramework/Actor.h"
#include "IntroSceneObject.generated.h"

UCLASS()
class MYPRO_API AIntroSceneObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIntroSceneObject();

protected:

	//FTimerHandle은 타이머를 관리하는 핸들이다.
	FTimerHandle Timerahbdle;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "listofSelctcharacter")
	TMap<Characters, ASelectCharacter*> SelectCharacterList; // 캐릭터 리스트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cutscene")
	TObjectPtr<ULevelSequence> CutsceneSequence;
	TObjectPtr <ULevelSequencePlayer> SequencePlayer;
	 ALevelSequenceActor* SequenceActor;
;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cutscene")
	TObjectPtr<UMediaPlayer> MyMediaPlayer_loading;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cutscene")
	TObjectPtr<UMediaPlayer> MyMediaPlayer_intro;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cutscene")
	TObjectPtr <UMediaSoundComponent> SoundComp;
	TSharedPtr<FStreamableHandle> Handle;
	UPROPERTY()
	TObjectPtr<UIntroMainUI> ui;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void CalltheSelectCharacter(Characters choice); // 캐릭터 선택 함수
	void CallthePlayCharacter(Characters choice); // 본게임에 들어갈때 플레이 할 캐릭터 선택
	// 시퀀스 플레이
	void PlaySequence();
	// 로딩 할때 나오는 비디오 
	void PlayloadingVideo();
	// 플레이신 비동기 로드 완료 될때 나오는 함수
	void PlaySceneLoad(const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result);
	// 플레이신 비동기 로드 
	void PlaySceneLoadAsync();
	void PlaySceneLoadAsync_stream();
	void LevelLoadComplete();
};
