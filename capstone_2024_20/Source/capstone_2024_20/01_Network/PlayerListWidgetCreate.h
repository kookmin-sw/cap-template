// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPlayerList.h"
#include "UObject/Object.h"

class UPlayerListWidget;

class CAPSTONE_2024_20_API PlayerListWidgetCreate :public IPlayerList
{
public:
	PlayerListWidgetCreate(UWorld* World, FString& WidgetName, UPlayerListWidget** PlayerListWidget, IPlayerList ** PlayerList);

	UWorld* CurrentWorld;
	FString PlayerListWidgetClass;
	UPlayerListWidget** ControllerPlayerListWidget;
	IPlayerList** ControllerPlayerList;
	
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	UPlayerListWidget* CreatePlayerListWidget();
};
