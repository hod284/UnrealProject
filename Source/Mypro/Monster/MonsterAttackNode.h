// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "Monster.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MonsterAttackNode.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UMonsterAttackNode : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	float PlusAttackRange =200.0f;
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector TargetKey;
	int32 Random;
	int32 CurrentRandom;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void  TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	UMonsterAttackNode();
};
