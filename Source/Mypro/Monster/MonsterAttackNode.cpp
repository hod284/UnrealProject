// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAttackNode.h"

UMonsterAttackNode::UMonsterAttackNode()
{
	NodeName = TEXT("AttackNode");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UMonsterAttackNode:: ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	float Distance = Monster->DistanceToTarget(Monster, TargetActor);
	if (Distance > BlackboardComp->GetValueAsFloat("SpecialAttackRange"))
	{
		return EBTNodeResult::Failed;
	}
	if (Distance < BlackboardComp->GetValueAsFloat("NoramlAttackRange"))
	{
		Random  =FMath::RandRange(0,1);
		CurrentRandom = Random; // ���� ���� ���� �����մϴ�.
	}
	else  
	{
		Random = FMath::RandRange(2, 3);
		CurrentRandom = Random; // ���� ���� ���� �����մϴ�.
	}
	switch (Random)
	{
	case 0:
		Monster->AnimInstance->MonsterAttack1();
		break;
	case 1:
		Monster->AnimInstance->MonsterAttack2();
		break;
	case 2:
		Monster->AnimInstance->MonsterAttack3();
		break;
	case 3:
		Monster->AnimInstance->MonsterAttack4();
		break;
	}
	return EBTNodeResult::InProgress;
}
EBTNodeResult::Type UMonsterAttackNode::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);
	return EBTNodeResult::Aborted;
}
void UMonsterAttackNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	AAIController* aicontroller = OwnerComp.GetAIOwner();
	if (!aicontroller|| !BlackboardComp)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	AMonster* Monster = Cast<AMonster>(aicontroller->GetPawn());
	if(!Monster)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
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
	if(BlackboardComp->GetValueAsBool("AttackEnd"))
	{
		BlackboardComp->SetValueAsBool("AttackEnd", false);
		float Distance = Monster->DistanceToTarget(Monster, TargetActor);
		if (Distance > BlackboardComp->GetValueAsFloat("SpecialAttackRange"))
		{
			// ������ �����ٸ� Task�� �����Ѵ�.
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return;
		}
		else if (Distance < BlackboardComp->GetValueAsFloat("SpecialAttackRange")&& Distance > BlackboardComp->GetValueAsFloat("NoramlAttackRange")|| Distance < BlackboardComp->GetValueAsFloat("NoramlAttackRange"))
		{
			FVector CurrentLocation = Monster->GetActorLocation();
			CurrentLocation.Z = 0;
			FVector TargetLocation = TargetActor->GetActorLocation();
			TargetLocation.Z = 0;
			FRotator Rot = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, TargetLocation);
			Monster->SetActorRotation(Rot);
		}
		if (Distance < BlackboardComp->GetValueAsFloat("NoramlAttackRange"))
		{
			Random = FMath::RandRange(0, 1);
			if (Random == CurrentRandom) // ���� ���� ���� ���ٸ� �ٽ� ������ �����մϴ�.
			{
				Random = FMath::RandRange(0, 1);
				CurrentRandom = Random; // ���� ���� ���� �����մϴ�.
			}
		}
		else
		{
			Random = FMath::RandRange(2, 3);
			if (Random == CurrentRandom) // ���� ���� ���� ���ٸ� �ٽ� ������ �����մϴ�.
			{
				Random = FMath::RandRange(2, 3);
				CurrentRandom = Random; // ���� ���� ���� �����մϴ�.
			}
		}
		switch (Random)
		{
		case 0:
			Monster->AnimInstance->MonsterAttack1();
			break;
		case 1:
			Monster->AnimInstance->MonsterAttack2();
			break;
		case 2:
			Monster->AnimInstance->MonsterAttack3();
			break;
		case 3:
			Monster->AnimInstance->MonsterAttack4();
			break;
		}
	}
}
void UMonsterAttackNode::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
	AMonster* Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if(Monster)
	{
		Monster->AnimInstance->IdleAni();
	}

}
