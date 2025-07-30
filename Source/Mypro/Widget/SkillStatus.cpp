// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillStatus.h"



void USkillStatus::Setinit(FName path, float timer)
{
	MyMat = UMaterialInstanceDynamic::Create(MyMaterial, this);
	// LoadObject<UTexture2D>() ù��° ���ڴ� nullptr������ �ڽİ��踦 ���� �� �ʿ䰡 ���� �����̴�
	MyMat->SetTextureParameterValue(FName("texture"), LoadObject<UTexture2D>(nullptr, *path.ToString()));
	MyMat->SetScalarParameterValue(FName("time"), timer);
	Image->SetBrushFromMaterial(MyMat);
}

void USkillStatus::SetTIme(float timer)
{
	MyMat->SetScalarParameterValue(FName("time"), timer);
	Image->SetBrushFromMaterial(MyMat);
}


