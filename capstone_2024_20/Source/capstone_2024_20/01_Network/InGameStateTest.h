// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "InGameStateTest.generated.h"

UCLASS()
class CAPSTONE_2024_20_API AInGameStateTest : public AGameStateBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Network")
	class ANetworkService* NetworkService;

	UFUNCTION()
	FName GetRoomCode() const;
};
