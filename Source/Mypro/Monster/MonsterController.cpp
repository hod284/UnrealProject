// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController.h"

AMonsterController::AMonsterController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SetPerceptionComponent(*AIPerception);
	//������� ����
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = DetectiveRange; //�þ� �ݰ�
	SightConfig->LoseSightRadius = DetectiveRange+200.0f; //�þ� �ս� �ݰ�
	SightConfig->PeripheralVisionAngleDegrees = 360.0f; //�þ� ����
	SightConfig->AutoSuccessRangeFromLastSeenLocation = DetectiveRange/2.0f; //���������� �� ��ġ���� ���� ����
	SightConfig->PointOfViewBackwardOffset = 0.0f; //���� �Ĺ� ������
	SightConfig->NearClippingRadius = 0.0f; //���� Ŭ���� �ݰ�
	SightConfig->DetectionByAffiliation.bDetectEnemies = true; //�� ���� ����
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false; //�Ʊ� ���� ����
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true; //�߸� ���� ����
	AIPerception->ConfigureSense(*SightConfig); //��������� �ð� ���� ����
	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));
	//���⼭ ���ϴ� Implementation �� "�� ������ � ���� Sense Ŭ������ �� �ǰ�" �� �����ϴ� �Լ�
	DamageConfig->Implementation = UAISense_Damage::StaticClass(); //������ ���� ����
	// ��������̳� ����� ������ ������ ���� ConfigureSense �Լ��� ����մϴ�.
	AIPerception->ConfigureSense(*DamageConfig); //��������� ������ ���� ����
	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation()); //�� ���� ����
	SetGenericTeamId(FGenericTeamId(TeamMonster));
}
void AMonsterController::BeginPlay()
{
	Super::BeginPlay();
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AMonsterController::OnTargetmethod);
	AIPerception->RequestStimuliListenerUpdate(); // ������
}
void AMonsterController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}
void AMonsterController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	// ��� �̵��� �������� ��쳪 �ߴܵǾ��� ���(Abort) ���.
	// ���� stopMovement�� ȣ���Ѵٸ� Result.Code == EPathFollowingResult::Aborted �̰� ����
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
		Blackboard->SetValueAsObject(TEXT("Target"), Target); // ���������� ������ ��� Ÿ�� ���͸� �����忡 ����
	else
		Blackboard->SetValueAsObject(TEXT("Target"), nullptr); // �������� ���� ��� Ÿ�� ���͸� nullptr�� ����
}
ETeamAttitude::Type AMonsterController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(&Other);
	if(!OtherTeamAgent)
		return ETeamAttitude::Neutral; // �ٸ� ������Ʈ�� GenericTeamAgentInterface�� �������� ���� ��� �߸����� ó��
	
	if(OtherTeamAgent ->GetGenericTeamId().GetId()== TeamNeutral)
		return ETeamAttitude::Neutral; // �߸� ���� ��� �߸����� ó��
	return GetGenericTeamId() == OtherTeamAgent->GetGenericTeamId() ?
		ETeamAttitude::Friendly : ETeamAttitude::Hostile;
}