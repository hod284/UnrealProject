// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterTraceNode.h"

UMonsterTraceNode::UMonsterTraceNode()
{
	NodeName = TEXT("TraceNode");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UMonsterTraceNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	// ���⼭ ���ϴ� fail�� �̳�尡 �����Ҽ� ������ �̳�带 �������� ����� �ǹ��̴�.
	if (!AIController || !BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}
	AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetKey.SelectedKeyName));
	// Ÿ���� �̵������� ��𿡼� �������� AceeptRadius�� �����Ѵ�.
	EPathFollowingRequestResult::Type Result = AIController->MoveToActor(TargetActor, BlackboardComp->GetValueAsFloat("NoramlAttackRange"));
	// ��ã�⿡ �����ߴ��� �Ǵ��Ѵ�.
	if (Result == EPathFollowingRequestResult::Failed)
	{
		return EBTNodeResult::Failed;
	}
	
	if (!TargetActor)
	{
		//Ÿ���� ��� �����ϼ������ǹ�
		//tick���� �ٽ� ã�����ϱ� ��� �������
		return EBTNodeResult::Succeeded;
	}
	AMonster* Monster = Cast<AMonster>(AIController->GetPawn());
	if (!Monster)
	{
		return EBTNodeResult::Failed;
	}
	if (Monster->GetStun() <= 0.0f)
	{
		return EBTNodeResult::Failed;
	}
	Monster->AnimInstance->RubAni();

	return EBTNodeResult::InProgress;
}
EBTNodeResult::Type UMonsterTraceNode::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if(AIController)
		AIController->StopMovement();
	return EBTNodeResult::Aborted;

}
void UMonsterTraceNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// ������������ ��尡 Selector�϶��� ����sequence �����϶� ������ ���� �����϶��� �׳� �����Ѵ�.
	//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); �̸��� ���⼺������ ��带 �����Ѵٶ�� �ǹ�
	//FinishLatentTask(OwnerComp, EBTNodeResult::Failed); �̳�� �����ߴٴ� �ǹ̷� ��带 �����ϰ� ����带 �����ض�
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	AAIController* AiController = OwnerComp.GetAIOwner();
	if (!AiController || !BlackboardComp)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	AMonster* Monster = Cast<AMonster>(AiController->GetPawn());
	if (!Monster)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	EPathFollowingStatus::Type PathStatus = AiController->GetMoveStatus();

	// �������� �������� �Ǵ��Ѵ�.
	if (PathStatus == EPathFollowingStatus::Idle)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetKey.SelectedKeyName));
	if (!TargetActor)
	{
		// Ÿ���� ���ٸ� Task�� �����Ѵ�.
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	if (Monster->GetStun() <= 0.0f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	float Distance = Monster->DistanceToTarget(Monster, TargetActor);
	UE_LOG(LogMypro, Warning, TEXT("Distance : %f"), Distance);
	UE_LOG(LogMypro, Warning, TEXT("Distance_n : %f"), BlackboardComp->GetValueAsFloat("NoramlAttackRange"));
	if (Distance <= BlackboardComp->GetValueAsFloat("NoramlAttackRange"))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
}
void UMonsterTraceNode::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
	AMonster* Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	AAIController* AIController = OwnerComp.GetAIOwner();
	if(Monster)
		Monster->AnimInstance->IdleAni();
}

