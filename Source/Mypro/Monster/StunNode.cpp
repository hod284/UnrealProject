// Fill out your copyright notice in the Description page of Project Settings.


#include "StunNode.h"

UStunNode::UStunNode()
{
	NodeName = TEXT("StunNode");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}
EBTNodeResult::Type UStunNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	AMonster* Monster = Cast<AMonster>(AIController->GetPawn());
	if (!Monster)
	{
		return EBTNodeResult::Failed;
	}
	if (Monster->GetStun() >= 1.0f)
	{
		return EBTNodeResult::Failed;
	}
	Monster->AnimInstance->StunAni();
	return EBTNodeResult::InProgress;
}
EBTNodeResult::Type UStunNode::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);
	return EBTNodeResult::Aborted;

}
void UStunNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	AAIController* aicontroller = OwnerComp.GetAIOwner();
	if (!aicontroller || !BlackboardComp)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	AMonster* Monster = Cast<AMonster>(aicontroller->GetPawn());
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
	if (Monster->GetStun() >= 1.0f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	else
	{
		Gage = FMath::Clamp(Gage + DeltaSeconds, 0.0f, 1.0f);
		Monster->SetStun(Gage);
	}
}
void UStunNode::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
	AMonster* Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	Gage = 0.0f;
	if (Monster)
		Monster->AnimInstance->IdleAni();
}

