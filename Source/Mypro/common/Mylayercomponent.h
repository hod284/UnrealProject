// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "Components/ActorComponent.h"
#include "Mylayercomponent.generated.h"

/*
����Ƽ���ִ� ������Ʈ���̾ ����������Ʈ�� �����Ѱ�
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPRO_API UMylayercomponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMylayercomponent();
	UPROPERTY(EditAnywhere, Category = "Layer")
	ObjestLayer LayerType;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
