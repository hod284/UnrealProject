// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController.h"

AMonsterController::AMonsterController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SetPerceptionComponent(*AIPerception);
	//감각기관 생성
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = DetectiveRange; //시야 반경
	SightConfig->LoseSightRadius = DetectiveRange+200.0f; //시야 손실 반경
	SightConfig->PeripheralVisionAngleDegrees = 360.0f; //시야 각도
	SightConfig->AutoSuccessRangeFromLastSeenLocation = DetectiveRange/2.0f; //마지막으로 본 위치에서 성공 범위
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
}
void AMonsterController::BeginPlay()
{
	Super::BeginPlay();
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AMonsterController::OnTargetmethod);
	AIPerception->RequestStimuliListenerUpdate(); // 선택적
}
void AMonsterController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}
void AMonsterController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	// 경로 이동이 성공했을 경우나 중단되었을 경우(Abort) 등등.
	// 만약 stopMovement를 호출한다면 Result.Code == EPathFollowingResult::Aborted 이게 성립
	if (Result.Code == EPathFollowingResult::Success|| Result.Code == EPathFollowingResult::Aborted)
	{
		ClearMovment();
	}
}
void AMonsterController::StopMovement()
{
	Super::StopMovement();
	ClearMovment();
}

void AMonsterController::ClearMovment()
{
	APawn* ControlPawn = GetPawn();
	if (ControlPawn)
	{
		UMonsterPawnMovement* MoveComp = Cast<UMonsterPawnMovement>(ControlPawn->GetMovementComponent());

		if (MoveComp)
		{
			MoveComp->ClearAIMoveDir();
		}
	}
}

void AMonsterController::OnTargetmethod(AActor* Target, FAIStimulus Stimulus)
{
	TSubclassOf<UAISense> SenseClass = UAIPerceptionSystem::GetSenseClassForStimulus(this,Stimulus);
	if(Stimulus.WasSuccessfullySensed())
		Blackboard->SetValueAsObject(TEXT("Target"), Target); // 성공적으로 감지된 경우 타겟 액터를 블랙보드에 설정
	else
		Blackboard->SetValueAsObject(TEXT("Target"), nullptr); // 감지되지 않은 경우 타겟 액터를 nullptr로 설정
}
ETeamAttitude::Type AMonsterController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(&Other);
	if(!OtherTeamAgent)
		return ETeamAttitude::Neutral; // 다른 에이전트가 GenericTeamAgentInterface를 구현하지 않은 경우 중립으로 처리
	
	if(OtherTeamAgent ->GetGenericTeamId().GetId()== TeamNeutral)
		return ETeamAttitude::Neutral; // 중립 팀인 경우 중립으로 처리
	return GetGenericTeamId() == OtherTeamAgent->GetGenericTeamId() ?
		ETeamAttitude::Friendly : ETeamAttitude::Hostile;
}