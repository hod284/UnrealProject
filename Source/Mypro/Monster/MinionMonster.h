// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "../Widget/MonsterHPBar.h"
#include "MonsterAnimInstance.h"
#include "MinionController.h"
#include "SkillActor/Action3_Monster.h"
#include "../common/MySingleton.h"
#include "MonsterPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "MinionMonster.generated.h"

UCLASS()
class MYPRO_API AMinionMonster : public APawn
{
	GENERATED_BODY()

protected:
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CusteomRange")
	float NoramlAttackRange = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CusteomRange")
	bool ShootingM = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UWidgetComponent> Damagesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionStimuliSourceComponent* StimuliSource;
	float HP = 1.0F;
	float MonsterHp;
	float MonsterHpConst;
	const FCMonsterInfo* Info;
	TObjectPtr<UBehaviorTree> MonsterBehaviorTree;
	FTimerHandle Timer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sk")
	TSubclassOf<AAction3_Monster> Sk3;
	AAction3_Monster* Ac3;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
	TObjectPtr<UMonsterAnimInstance> AnimInstance;
	EMonsterDefaultAnim MonSterAnim;
public:
	void AttackSuper();
	void AttackShooting();
	void AttackShootingEnd();
	void Death();
	void Idle_M();
	void Attack_M();
	void Death_M();
	void Run_M();
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PlayAttack(EMonsterDefaultAnim type);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_Run(EMonsterDefaultAnim type);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_Death(EMonsterDefaultAnim type);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_idle(EMonsterDefaultAnim type);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_Sethp(float hp);
	UFUNCTION(Server, Reliable)
	void Server_PlayAttack(EMonsterDefaultAnim type);

	UFUNCTION(Server, Reliable)
	void Server_Run(EMonsterDefaultAnim type);

	UFUNCTION(Server, Reliable)
	void Server_Death(EMonsterDefaultAnim type);

	UFUNCTION(Server, Reliable)
	void Server_idle(EMonsterDefaultAnim type);
	UFUNCTION(Server, Reliable)
	void Server_Sethp(float hp);
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
	bool GetShootingM() const
	{
		return  ShootingM;
	}
	TObjectPtr<USkeletalMeshComponent> GetMesh()
	{
		return MeshComponent;
	}
	TObjectPtr<UMonsterAnimInstance> GetAnimInstance()
	{
		return AnimInstance;
	}
	EMonsterDefaultAnim GetMonSterAnim()
	{
		return MonSterAnim;
	}
};
