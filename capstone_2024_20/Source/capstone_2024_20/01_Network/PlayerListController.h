// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPlayerList.h"
#include "GameFramework/Actor.h"

class UPlayerListWidget;

class CAPSTONE_2024_20_API FPlayerListController : public IPlayerList
{

public:
	FPlayerListController(UWorld* World);

private:
	UPlayerListWidget* PlayerListWidget;
	IPlayerList* PlayerListUpdate;
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
