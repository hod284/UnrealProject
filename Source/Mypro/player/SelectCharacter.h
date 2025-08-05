// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "GameFramework/Pawn.h"
#include "SelectCharacter.generated.h"
/*
ĳ���� ������ �� ���̴� ĳ���� ���ÿ� Pawn Ŭ�����Դϴ�.
*/
UCLASS()
class MYPRO_API ASelectCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASelectCharacter();

protected:
	//FTimerHandle�� Ÿ�̸Ӹ� �����ϴ� �ڵ��̴�.
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
	TObjectPtr<UAnimSequence> SelectedAnim; // ���� �ִϸ��̼�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "value")
	TObjectPtr<UAnimSequence> idle; // �⺻�ִϸ��̼�

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// ĳ���ʹ�ǥ�ϴ� ĳ���� �����Ҷ� ������ �Լ�
	void Selected();
	// ĳ���� ������ ��  selectedAnim �ִϸ��̼� �����ϴ� �Լ� 
	void SelectedAnimation();
	// ĳ���� ������ �� idle �ִϸ��̼� �����ϴ� �Լ�
	void idleAnimation();
	// ĳ���� �ٸ��� �����Ҷ� �ʱ�ȭ�Լ�
	void Inite();
	void StartGame();
};
