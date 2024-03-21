// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPlayerList.h"
#include "PlayerListWidget.h"
#include "UObject/Object.h"

/**
 * 
 */
class CAPSTONE_2024_20_API UPlayerListWidgetModifier : public IPlayerList
{
public:
	UPlayerListWidgetModifier(UPlayerListWidget* NewPlayerListWidget);
private:
	UPlayerListWidget* PlayerListWidget;

	TMap<int32, int32> IdIndexMap;
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
};
