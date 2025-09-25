// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "MinionMonster.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MinionAttackNode.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UMinionAttackNode : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector TargetKey;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void  TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	UMinionAttackNode();
};
