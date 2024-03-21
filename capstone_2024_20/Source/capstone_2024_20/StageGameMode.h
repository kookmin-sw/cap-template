// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Network/IPlayerList.h"
#include "01_Network/PlayerListController.h"
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

	IPlayerList* PlayerListController = new FPlayerListController(GetWorld());

public:
	class AStageSelectController* StageSelectController;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
};
