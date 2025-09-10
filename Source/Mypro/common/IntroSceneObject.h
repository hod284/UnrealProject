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

	FTimerHandle Timerhandle;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "listofSelctcharacter")
	TMap<Characters, ASelectCharacter*> SelectCharacterList; 
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
	void CalltheSelectCharacter(Characters choice); // ĳ���� ���� �Լ�
	void CallthePlayCharacter(Characters choice); // �����ӿ� ���� �÷��� �� ĳ���� ����

	void PlayloadingVideo();
	void PlaySceneLoad(const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result);

	void PlaySceneLoadAsync();

	void PlaySceneLoadAsync_stream();

	void LevelLoadComplete();

};
