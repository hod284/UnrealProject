// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../Widget/MonsterHPBar.h"
#include "MonsterAnimInstance.h"
#include "MinionController.h"
#include "MonsterPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "MinionMonster.generated.h"

UCLASS()
class MYPRO_API AMinionMonster : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMinionMonster();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UMonsterPawnMovement> MovementComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UMaterial> Overlap;
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
	UPROPERTY(ReplicatedUsing = OnRep_Health)
	float HP = 1.0F;
	float MonsterHp;
	bool Death = false;
	UBrainComponent* Brain;
	const FCMonsterInfo* Info;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UWidgetComponent> Damagesh;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)  const override;

	UFUNCTION()
	void OnRep_Health();

public:
	void AttackSuper();
	void AttackShooting();
	TObjectPtr<UMonsterAnimInstance> AnimInstance;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
	float DistanceToTarget(AActor* Target)
	{
		float dis = 0.0f;
		FVector	TargetLocation, MonsterLocation;
		TargetLocation = FVector(Target->GetActorLocation().X, Target->GetActorLocation().Y, 0);

		MonsterLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0);

		dis = FVector::Dist(TargetLocation, MonsterLocation);
		return dis;
	}
	void SetMonsterHP(float NewHP)
	{
		MonsterHp = NewHP;
	}
	float GetHP() const
	{
		return HP;
	}
	float GetDeath() const
	{
		return Death;
	}

};
