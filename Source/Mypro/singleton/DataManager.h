// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Gameinfo.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataManager.generated.h"

/**
 * 
 */
UCLASS()
class MYPRO_API UDataManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
protected:

		virtual void Initialize(FSubsystemCollectionBase& Collection) override;
		const FCharacterInfo* Datainfo_W;
		const FCharacterInfo* Datainfo_G;
		const FCharacterInfo* Datainfo_D;
public:
	const FCharacterInfo* GetDatainfo_W() const
	{
		return Datainfo_W;
	}
	const FCharacterInfo* GetDatainfo_G() const
	{
		return Datainfo_G;
	}
	const FCharacterInfo* GetDatainfo_D() const
	{
		return Datainfo_D;
	}
};
