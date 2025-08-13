// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "GameFramework/Pawn.h"
#include "SelectCharacter.generated.h"
/*
캐릭터 선택할 때 쓰이는 캐릭터 선택용 Pawn 클래스입니다.
*/
UCLASS()
class MYPRO_API ASelectCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASelectCharacter();

protected:
	//FTimerHandle은 타이머를 관리하는 핸들이다.
	FTimerHandle Timerahbdle;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCapsuleComponent> CapsulComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "value")
	TObjectPtr<UAnimSequence> SelectedAnim; // 선택 애니메이션
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "value")
	TObjectPtr<UAnimSequence> idle; // 기본애니메이션
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraComponent> Niagara; // 나이아가라 파티클

	bool IsHover; // 마우스 커서가 오버되었는지 확인하는 변수
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginCursorOver() override;
	virtual void NotifyActorEndCursorOver()   override;
	virtual void NotifyActorOnClicked(FKey ButtonPressed)    override;
public:	
	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// 캐릭터대표하는 캐릭터 선택할때 실행할 함수
	void Selected();
	// 캐릭터 선택할 때  selectedAnim 애니메이션 실행하는 함수 
	void SelectedAnimation();
	// 캐릭터 선택할 때 idle 애니메이션 실행하는 함수
	void idleAnimation();
	// 캐릭터 다른거 선택할때 초기화함수
	void Inite();
	// 캐릭터 선택하고 본게임 들어가는 함수
	void StartGame();
};
