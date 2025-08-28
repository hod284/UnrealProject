// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillStatus.h"



void USkillStatus::Setinit(FString path, float timer)
{
	MyMat = UMaterialInstanceDynamic::Create(MyMaterial, this);
	// LoadObject<UTexture2D>() 첫번째 인자는 nullptr이유는 자식관계를 설정 할 필요가 없기 때문이다
	UTexture2D* SoftTexture = LoadObject<UTexture2D>(nullptr, *path);
	MyMat->SetTextureParameterValue(FName("texture"), SoftTexture);
	MyMat->SetScalarParameterValue(FName("time"), timer);
	Image->SetBrushFromMaterial(MyMat);
}

void USkillStatus::SetTIme(float timer)
{
	MyMat->SetScalarParameterValue(FName("time"), timer);
	Image->SetBrushFromMaterial(MyMat);
}


