// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include  "../singleton/GameManager.h"
#include "../common/PlaySceneObject.h"
#include "MyPlayerAnimInstance.h"
#include "MaInPlayerController.h"
#include "../singleton/InputManager.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class MYPRO_API AMyCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
private:
protected:
	AMainPlayerController* PlayerController;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraComponent> Niagara;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> SpringArm;
	TObjectPtr<UMyPlayerAnimInstance> AnimInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> CameraHead;
	// 플레이어 급백 방향
	FVector CurrentVelocity;
	bool DashMoving = false;// 대쉬기능
	bool BackMoving = false;// 백기능
	bool IsMoving = false;// 이동중인지 아닌지
	bool LookAt = true;// 카메라 바라보기
	bool CameraRo = false;// 카메라 돌리기
	bool CanPortal = false;// 카메라 돌리기
	FGenericTeamId	TeamID;
	float HP = 1.0F;
	float MP = 1.0F;
	float PlayerHp_Const;
	float PlayerHp;
	float PlayerMp_Const;
	float PlayerMp;
    APlaySceneObject* PlaySceneObject;
	FTimerHandle DashTimer;
	float SavedGroundFriction = 8.f;
	float SavedBrakingFriction = 8.f;
	float SavedBrakingDecel = 2048.f;
	UPlayMainUI* ui;
	bool Canskill1 = true;
	float Skill1cool = 1.0F;
	float Skill1Speed = 0.0F;
	bool Canskill2 =true;
	float Skill2cool = 1.0F;
	float Skill2Speed = 0.0F;
	bool Canskill3 =true;
	float Skill3cool = 1.0F;
	float Skill3Speed = 0.0F;
	bool Canskill4 =true;
	float Skill4cool = 1.0F;
	float Skill4Speed = 0.0F;
	FVector TargetLocation;
	USceneComponent* TargetTransform;
	int32 AttackDamage;
	int32 AttackDamageUp;
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
	// 백대쉬 끝날때 호출
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
	void DashKey(const FInputActionValue& Value);
	void InventoryKey(const FInputActionValue& Value);
	void Skill1coolTime(float speed);
	void Skill2coolTime(float speed);
	void Skill3coolTime(float speed);
	void Skill4coolTime(float speed);
	void MpbarSync(float cost);
	void AddMpbar(float cost);
	// Sets default values for this character's properties
	AMyCharacter();
public:	
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PlayMontageAttack(bool up, int32 inde);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PlayMontageSkill(int32 index);
	UFUNCTION(Server, Reliable)
	void Server_PlayMontageAttack(bool up, int32 index);
	UFUNCTION(Server, Reliable)
	void Server_PlayMontageSkill(int32 index);
	void SendtheMontageAttack(bool up, int32 index);
	void SendtheMontageSkill(int32 index);
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
	void SetBackMoving(bool moving)
	{
		BackMoving = moving;
	}
	bool GetBackMoving() const
	{
		return BackMoving;
	}
   bool GetDashMoving() const
	{
	   return DashMoving;
	}
	bool GetCanskill3()
	{
		return Canskill3;
	}
	float GetHP() const
	{
		return HP;
	}
	float GetMP() const
	{
		return MP;
	}
	bool GetCanPortal() const
	{
		return CanPortal;
	}
	void SetAddCanPortal(FString name)
	{
		if (name == "Portal")
			CanPortal = true;
	}
	void SetMinusCanPortal(FString name)
	{
		if (name == "Portal")
			CanPortal = false;
	}
	void SetColision(FString cporfile)
	{
	    GetCapsuleComponent()->SetCollisionProfileName(FName(*cporfile));
	}
};
