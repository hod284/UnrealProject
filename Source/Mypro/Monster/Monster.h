// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "GameFramework/Pawn.h"
#include "MonsterController.h"
#include "MonsterPawnMovement.h"
#include "MonsterAnimInstance.h"
#include "../singleton/UImanager.h"
#include "../singleton/DataManager.h"
#include "../common/PortalClass.h"
#include "SkillActor/Action1_Monster.h"
#include "SkillActor/Action2_Monster.h"
#include "SkillActor/Action3_Monster.h"
#include "SkillActor/Action4_Monster.h"
#include "Monster.generated.h"

UCLASS()
class MYPRO_API AMonster : public APawn,
	// IGenericTeamAgentInterface 라는 인터페이스 상속받아서 현재 자신의 소속이 어딘지설정
	public IGenericTeamAgentInterface
{
	GENERATED_BODY()

protected:
	// Sets default values for this pawn's properties
	AMonster();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UMonsterPawnMovement> MovementComponent;
	FGenericTeamId	TeamID;
	TObjectPtr<UBehaviorTree> MonsterBehaviorTree;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CusteomRange")
	float NoramlAttackRange = 200.0f;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FTimerHandle TimeSkill;
	float HP = 1.0F;
	float Stun = 1.0F;
	float MonsterHp;
	float MonsterStun;
	bool CanStun=true;
	bool Death = false;
	UBrainComponent* Brain;
	const FCMonsterInfo* Info;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sk")
	TSubclassOf<AAction1_Monster> Sk1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sk")
	TSubclassOf<AAction2_Monster> Sk2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sk")
	TSubclassOf<AAction3_Monster> Sk3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sk")
	TSubclassOf<AAction4_Monster> Sk4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "portal")
	TSubclassOf<APortalClass> Portal;
	UPlayMainUI* UI;
public:	
	void Start();
	void Attack1();
	void Attack2();
	void Attack3();
	void Attack4();
	AAction1_Monster* Ac1;
	AAction2_Monster* Ac2;
	AAction3_Monster* Ac3;
	AAction4_Monster* Ac4;
	TObjectPtr<UMonsterAnimInstance> AnimInstance;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
	// IGenericTeamAgentInterface 라는 인터페이스 에서 구현해야할 함수
	virtual FGenericTeamId GetGenericTeamId()	const  override
	{
		return TeamID;
	}
	void SetGenericTeamId(const FGenericTeamId& mTeamID) 
	{
		TeamID = mTeamID;
	}
	float DistanceToTarget( AActor* Target)
	{
		float dis = 0.0f;
		FVector	TargetLocation, MonsterLocation;
		TargetLocation = FVector(Target->GetActorLocation().X, Target->GetActorLocation().Y,0);

		// 몬스터 위치를 구한다.
		MonsterLocation = FVector( GetActorLocation().X, GetActorLocation().Y,0);

		// 둘 사이의 거리를 구한다.
		dis = FVector::Dist(TargetLocation, MonsterLocation);
		return dis;
	}
	void SetMonsterHP(float NewHP)
	{
		MonsterHp = NewHP;
	}
	void SetMonsterStun(float st);
	void SetCanStun(bool bo)
	{
		CanStun =bo;
		if(bo)
		UI->OnStunDamage.Broadcast(1.0);
	}
	float GetHP() const
	{
		return HP;
	}
	float GetStun() const
	{
		return Stun;
	}
	float GetDeath() const
	{
		return Death;
	}
	AAction1_Monster* GetAAction1_Monster()const
	{
		return  Ac1;
	}
	AAction2_Monster* GetAAction2_Monster()const
	{
		return  Ac2;
	}
	AAction3_Monster* GetAAction3_Monster()const
	{
		return  Ac3;
	}
	AAction4_Monster* GetAAction4_Monster()const
	{
		return  Ac4;
	}
};
