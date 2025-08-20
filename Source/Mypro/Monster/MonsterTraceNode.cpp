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
	// 여기서 말하는 fail는 이노드가 실행할수 없으니 이노드를 실행하지 마라는 의미이다.
	if (!AIController || !BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}
	AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetKey.SelectedKeyName));
	// 타겟이 이동했을때 어디에서 멈출지를 AceeptRadius로 설정한다.
	EPathFollowingRequestResult::Type Result = AIController->MoveToActor(TargetActor, BlackboardComp->GetValueAsFloat("NoramlAttackRange"));
	// 길찾기에 성공했는지 판단한다.
	if (Result == EPathFollowingRequestResult::Failed)
	{
		return EBTNodeResult::Failed;
	}
	
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
	// 어디까지난위의 노드가 Selector일때임 만약sequence 성공일때 옆노드로 가고 실패일때는 그냥 종료한다.
	//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); 이말은 여기성공으로 노드를 종료한다라는 의미
	//FinishLatentTask(OwnerComp, EBTNodeResult::Failed); 이노듣 실패했다는 의미로 노드를 종료하고 옆노드를 실해해라
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

	// 도착인지 실패인지 판단한다.
	if (PathStatus == EPathFollowingStatus::Idle)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetKey.SelectedKeyName));
	if (!TargetActor)
	{
		// 타겟이 없다면 Task를 종료한다.
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

