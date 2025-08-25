// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "GameFramework/Pawn.h"
#include "MonsterController.h"
#include "MonsterPawnMovement.h"
#include "MonsterAnimInstance.h"
#include "Monster.generated.h"

UCLASS()
class MYPRO_API AMonster : public APawn,
	// IGenericTeamAgentInterface ��� �������̽� ��ӹ޾Ƽ� ���� �ڽ��� �Ҽ��� ���������
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
	float NoramlAttackRange = 100.0f;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	float HP = 1.0F;
	float Stun = 1.0F;
	int32 MonsterHp;
	int32 MonsterStun;
	UBrainComponent* Brain;
public:	
	void Start();
	TObjectPtr<UMonsterAnimInstance> AnimInstance;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
	// IGenericTeamAgentInterface ��� �������̽� ���� �����ؾ��� �Լ�
	virtual FGenericTeamId GetGenericTeamId()	const  override
	{
		return TeamID;
	}
	void SetGenericTeamId(const FGenericTeamId& mTeamID) 
	{
		TeamID = mTeamID;
	}
	float DistanceToTarget(AMonster* Monster, AActor* Target)
	{
		float dis = 0.0f;
		FVector	TargetLocation, MonsterLocation;
		// Ÿ���� ��ġ�� ���´�. ��, �߹� ����� �������� ��ġ�� ������ ���̱� ������ ĸ����
		// ���� ���̸�ŭ�� �Ʒ��� ���� ��ġ�� ���Ѵ�.
		TargetLocation = Target->GetActorLocation();

		// ��Ʈ������Ʈ�� ĸ���� ��� ���� ���̸�ŭ�� �Ʒ��� �����ش�.
		UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(Target->GetRootComponent());

		if (Capsule)
		{
			TargetLocation.Z -= Capsule->GetScaledCapsuleHalfHeight();
		}

		// ���� ��ġ�� ���Ѵ�.
		MonsterLocation = Monster->GetActorLocation();

		Capsule = Cast<UCapsuleComponent>(Monster->GetRootComponent());

		// ���ʹ� ��Ʈ������Ʈ�� ������ Capsule�� ������ �ִ�.
		MonsterLocation.Z -= Capsule->GetScaledCapsuleHalfHeight();

		// �� ������ �Ÿ��� ���Ѵ�.
		dis = FVector::Dist(TargetLocation, MonsterLocation);
		return dis;
	}
	void SetHP(float NewHP)
	{
		HP = NewHP;
	}
	void SetStun(float NewStun)
	{
		Stun = NewStun;
	}
	float GetHP() const
	{
		return HP;
	}
	float GetStun() const
	{
		return Stun;
	}

};
