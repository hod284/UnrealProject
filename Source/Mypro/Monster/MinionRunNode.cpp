// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionRunNode.h"

UMinionRunNode::UMinionRunNode()
{
	NodeName = TEXT("TraceNode");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UMinionRunNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
    AMinionMonster* Monster = Cast<AMinionMonster>(AIController->GetPawn());
	if (!Monster)
	{
		return EBTNodeResult::Failed;
	}
	AMinionController* minioncontroller = Cast<AMinionController>(AIController);
	if (minioncontroller)
	minioncontroller->Run_M();
	return EBTNodeResult::InProgress;
}
EBTNodeResult::Type UMinionRunNode::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
		AIController->StopMovement();
	return EBTNodeResult::Aborted;

}
void UMinionRunNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	AAIController* AiController = OwnerComp.GetAIOwner();
	if (!AiController || !BlackboardComp)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	AMinionMonster* Monster = Cast<AMinionMonster>(AiController->GetPawn());
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
	EPathFollowingStatus::Type PathStatus = AiController->GetMoveStatus();

	// 도착인지 실패인지 판단한다.
	// mopvetoactor영향으로 멈춤
	if (PathStatus == EPathFollowingStatus::Idle)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	float Distance = Monster->DistanceToTarget(TargetActor);
	UE_LOG(LogMypro, Warning, TEXT("Distance : %f"), Distance);
	UE_LOG(LogMypro, Warning, TEXT("Distance_n : %f"), BlackboardComp->GetValueAsFloat("NoramlAttackRange"));
	if (Distance <= BlackboardComp->GetValueAsFloat("NoramlAttackRange"))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
}
void UMinionRunNode::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
	AAIController* AIController = OwnerComp.GetAIOwner();
	AMinionController* minioncontroller = Cast<AMinionController>(AIController);
	if (minioncontroller)
		minioncontroller->Idle_M();
}

