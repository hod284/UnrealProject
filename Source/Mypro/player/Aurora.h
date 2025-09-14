// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyCharacter.h"
#include "OtherSkill/Skill1_Actor.h"
#include "OtherSkill/Skill2_Actor.h"
#include "OtherSkill/Skill4_Actor.h"
#include "Aurora.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API AAurora : public AMyCharacter
{
	GENERATED_BODY()
	
protected:
	const FCharacterInfo* Info;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sk")
	TSubclassOf<ASkill1_Actor> Sk1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sk")
	TSubclassOf<ASkill2_Actor> Sk2;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "sk")
	TSubclassOf<ASkill4_Actor> Sk4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sk")
	TObjectPtr<UMaterialInterface> Mat;
	ASkill1_Actor* A1;
	ASkill2_Actor* A2;
	ASkill4_Actor* A4;
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PlaySkill1(FTransform form);
	UFUNCTION(Server, Reliable)
	void Server_PlaySkill1(FTransform form);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PlaySkill2(FTransform form);
	UFUNCTION(Server, Reliable)
	void Server_PlaySkill2(FTransform form);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PlaySkill3();
	UFUNCTION(Server, Reliable)
	void Server_PlaySkill3();
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PlaySkill4(FTransform form);
	UFUNCTION(Server, Reliable)
	void Server_PlaySkill4(FTransform form);
	virtual void BeginPlay() override;
public:

	AAurora();
	virtual void NAttack() override;
	virtual void  Skill1() override;
	virtual void  Skill2()override;
	virtual void  Skill3()override;
	virtual void  Skill4()override;
};
