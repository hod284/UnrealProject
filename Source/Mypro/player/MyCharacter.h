// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include  "../singleton/GameManager.h"
#include "MyPlayerAnimInstance.h"
#include "MaInPlayerController.h"
#include "../singleton/InputManager.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class MYPRO_API AMyCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> SpringArm;
	TObjectPtr<UMyPlayerAnimInstance> AnimInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> CameraHead;
	// 플레이어 급백 방향
	FVector CurrentVelocity;
	bool BackMoving = false;// 백기능
	bool IsMoving = false;// 이동중인지 아닌지
	bool LookAt = false;// 카메라 바라보기
	FGenericTeamId	TeamID;
	float HP = 1.0F;
	float MP = 1.0F;
	int32 PlayerHp;
	int32 PlayerMp;
    APlaySceneObject* PlaySceneObject;
	FTimerHandle DashTimer;
	float SavedGroundFriction = 8.f;
	float SavedBrakingFriction = 8.f;
	float SavedBrakingDecel = 2048.f;
	// 충돌
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);
	// 오버랩
	UFUNCTION()
	void OnCapsuleBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	// 오버랩 끝
	UFUNCTION()
	void OnCapsuleEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
	// 대쉬 끝날때 호출
	void EndDash();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void MoveKey(const FInputActionValue& Value);
	void CameraRotation(const FInputActionValue& Value);
	void CameraRotation_Allow(const FInputActionValue& Value);
	void CameraRotation_Cancel(const FInputActionValue& Value);
	void MoveStop(const FInputActionValue& Value);
	void BackKey(const FInputActionValue& Value);
	void AttackKey(const FInputActionValue& Value);
	void Skill1Key(const FInputActionValue& Value);
	void Skill2Key(const FInputActionValue& Value);
	void Skill3Key(const FInputActionValue& Value);
	void Skill4Key(const FInputActionValue& Value);
public:	
	
	// 가상함수 
	virtual void NAttack();
	virtual void  Skill1();
	virtual void  Skill2();
	virtual void  Skill3();
	virtual void  Skill4();
	virtual FGenericTeamId GetGenericTeamId()	const override
	{
		return TeamID;
	}
    void SetGenericTeamId(const FGenericTeamId& mTeamID)
	{
		TeamID = mTeamID;
	}
	void SetHP(float NewHP)
	{
		HP = NewHP;
	}
	void SetMP(float NewMP)
	{
		MP = NewMP;
	}
	float GetHP() const
	{
		return HP;
	}
	float GetMP() const
	{
		return MP;
	}
};
