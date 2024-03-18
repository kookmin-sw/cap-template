// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StageGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_2024_20_API AStageGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	class AStageSelectController* StageSelectController;
};
