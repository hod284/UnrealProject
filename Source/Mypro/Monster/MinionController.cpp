// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionController.h"
#include "../player/MainPlayerController.h"
#include "../player/MyPlayerState.h"
#include "MinionMonster.h"
AMinionController::AMinionController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SetPerceptionComponent(*AIPerception);
	//감각기관 생성
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = DetectiveRange; //시야 반경
	SightConfig->LoseSightRadius = DetectiveRange + 200.0f; //시야 손실 반경
	SightConfig->PeripheralVisionAngleDegrees = 360.0f; //시야 각도
	SightConfig->AutoSuccessRangeFromLastSeenLocation = DetectiveRange / 2.0f; //마지막으로 본 위치에서 성공 범위
	SightConfig->PointOfViewBackwardOffset = 0.0f; //시점 후방 오프셋
	SightConfig->NearClippingRadius = 0.0f; //근접 클리핑 반경
	SightConfig->DetectionByAffiliation.bDetectEnemies = true; //적 감지 여부
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false; //아군 감지 여부
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true; //중립 감지 여부
	AIPerception->ConfigureSense(*SightConfig); //감각기관에 시각 감각 설정
	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));
	//여기서 말하는 Implementation 은 "이 설정이 어떤 실제 Sense 클래스를 쓸 건가" 를 리턴하는 함수
	DamageConfig->Implementation = UAISense_Damage::StaticClass(); //데미지 감각 설정
	// 감각기관이나 기관의 설정을 변경할 때는 ConfigureSense 함수를 사용합니다.
	AIPerception->ConfigureSense(*DamageConfig); //감각기관에 데미지 감각 설정
	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation()); //주 감각 설정
	SetGenericTeamId(FGenericTeamId(TeamMonster));
	SetReplicates(true);
}
void  AMinionController::BeginPlay()
{
	Super::BeginPlay();

}
void AMinionController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto TA = Blackboard->GetValueAsObject(TEXT("Target"));
	if (TA == NULL)
	{
		Count = 0;
		for (TActorIterator<AMyCharacter> It(GetWorld()); It; ++It)
		{
			Count++;
			One = *It;
		}
		if (Count > 1)
		{
			PerceivedActors.Reset();
			PerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);
			float ClosestDistance = TNumericLimits<float>::Max();

			for (AActor* Actor : PerceivedActors)
			{
				AMyCharacter* Pa = Cast<AMyCharacter>(Actor);
				if (Pa)
				{
					FString name = "";

					APlayerController* PC = GetWorld()->GetFirstPlayerController();
					AMyPlayerState* PS = PC->GetPlayerState<AMyPlayerState>();
					if (HasAuthority())
						name = PS->TargetName;
					else
					{
						AMainPlayerController* MPC = Cast<AMainPlayerController>(PC);
						MPC->Server_GetttheTargetName();
						name = MPC->TargetName;
					}

					if (Actor->GetName() == name)
					{
						continue;
					}
					else
					{
						float Distance = FVector::DistSquared(Actor->GetActorLocation(), GetPawn()->GetActorLocation());
						if (Distance < ClosestDistance)
							ClosestActor = Actor;
					}
				}
			}
		}
		else
		{
				ClosestActor = One;
		}
		if (ClosestActor)
		{
			APlayerController* PC = GetWorld()->GetFirstPlayerController();
			AMyPlayerState* PS = PC->GetPlayerState<AMyPlayerState>();
			if (HasAuthority())
				PS->TargetName = ClosestActor->GetName();
			else
			{
				AMainPlayerController* MPC = Cast<AMainPlayerController>(PC);
				MPC->Server_SendttheTargetName(ClosestActor->GetName()); 
			}
			Blackboard->SetValueAsObject(TEXT("Target"), ClosestActor);
		}
		else
		{
			Blackboard->SetValueAsObject(TEXT("Target"), nullptr);
		}
	}
}
void  AMinionController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}
void  AMinionController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	// 경로 이동이 성공했을 경우나 중단되었을 경우(Abort) 등등.
	// 만약 stopMovement를 호출한다면 Result.Code == EPathFollowingResult::Aborted 이게 성립
	if (Result.Code == EPathFollowingResult::Success || Result.Code == EPathFollowingResult::Aborted)
	{
		ClearMovment();
	}
}
void  AMinionController::StopMovement()
{
	Super::StopMovement();
	ClearMovment();
}

void  AMinionController::ClearMovment()
{
	APawn* ControlPawn = GetPawn();
	if (ControlPawn)
	{
		UMonsterPawnMovement* MoveComp = Cast<UMonsterPawnMovement>(ControlPawn->GetMovementComponent());

		if (MoveComp)
		{
			//pawn의 MovementComponent에서 현재 움직이는 방향을 벡터zero로 설정 움직임 정지
			MoveComp->ClearAIMoveDir();
		}
	}
}


ETeamAttitude::Type  AMinionController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(&Other);
	if (!OtherTeamAgent)
		return ETeamAttitude::Neutral; // 다른 에이전트가 GenericTeamAgentInterface를 구현하지 않은 경우 중립으로 처리

	if (OtherTeamAgent->GetGenericTeamId().GetId() == TeamNeutral)
		return ETeamAttitude::Neutral; // 중립 팀인 경우 중립으로 처리
	// GenericTeamAgentInterface를 구현한 다른 에이전트와 비교하여 팀 태도 결정
	return GetGenericTeamId() == OtherTeamAgent->GetGenericTeamId() ?
		ETeamAttitude::Friendly : ETeamAttitude::Hostile;
}
