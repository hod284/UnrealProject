// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "Blueprint/UserWidget.h"
#include "SkillStatus.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API USkillStatus : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TObjectPtr<UMaterialInterface> MyMaterial;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> Image;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UMaterialInstanceDynamic> MyMat;
	
	void Setinit(FName path, float timer); 
	void SetTIme(float timer);

	
};
