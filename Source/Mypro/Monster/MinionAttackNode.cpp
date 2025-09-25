// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionAttackNode.h"

UMinionAttackNode::UMinionAttackNode()
{
	NodeName = TEXT("AttackNode");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type  UMinionAttackNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!AIController || !BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}
	AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetKey.SelectedKeyName));
	if (!TargetActor)
	{
		//타겟이 없어도 진행하세요라는의미
		//tick에서 다시 찾을꺼니까 없어도 상관없음
		return EBTNodeResult::Succeeded;
	}
	AMinionMonster* Monster = Cast< AMinionMonster>(AIController->GetPawn());
	if (!Monster)
	{
		return EBTNodeResult::Failed;
	}
	AMinionController* minioncontroller = Cast<AMinionController>(AIController);
	if (minioncontroller)
		minioncontroller->Attack_M();
	return EBTNodeResult::InProgress;
}
EBTNodeResult::Type  UMinionAttackNode::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);
	return EBTNodeResult::Aborted;
}
void  UMinionAttackNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	AAIController* aicontroller = OwnerComp.GetAIOwner();
	if (!aicontroller || !BlackboardComp)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	AMinionMonster* Monster = Cast<AMinionMonster>(aicontroller->GetPawn());
	if (!Monster)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetKey.SelectedKeyName));
	if (!TargetActor)
	{
		// 타겟이 없다면 Task를 종료한다.
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	} 
	if (BlackboardComp->GetValueAsBool("AttackEnd"))
	{
		BlackboardComp->SetValueAsBool("AttackEnd", false);
		float Distance = Monster->DistanceToTarget(TargetActor);
		if (Distance > BlackboardComp->GetValueAsFloat("NoramlAttackRange"))
		{
			// 공격이 끝났다면 Task를 종료한다.
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return;
		}
		else
		{
			FVector CurrentLocation = Monster->GetActorLocation();
			CurrentLocation.Z = 0;
			FVector TargetLocation = TargetActor->GetActorLocation();
			TargetLocation.Z = 0;
			FRotator Rot = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, TargetLocation);
			Monster->SetActorRotation(Rot);
		}
		if (Distance <= BlackboardComp->GetValueAsFloat("NoramlAttackRange"))
		{
			AMinionController* minioncontroller = Cast<AMinionController>(aicontroller);
			if (minioncontroller)
				minioncontroller->Attack_M();
		}
	}
}
void  UMinionAttackNode::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
	AAIController* AIController = OwnerComp.GetAIOwner();
	AMinionController* minioncontroller = Cast<AMinionController>(AIController);
	if (minioncontroller)
		minioncontroller->Idle_M();
}
