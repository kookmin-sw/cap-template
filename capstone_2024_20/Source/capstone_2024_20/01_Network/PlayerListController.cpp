// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerListController.h"

#include "PlayerListWidgetCreate.h"
#include "PlayerListWidgetModifier.h"

FPlayerListController::FPlayerListController(UWorld* World)
{
	FString WidgetName = "BP_PlayerListWidget";
	PlayerListWidgetCreate* PlayerListWigetCreate = new PlayerListWidgetCreate(World, WidgetName,
		&PlayerListWidget, &PlayerListUpdate);
	PlayerListUpdate = PlayerListWigetCreate;
}

void FPlayerListController::PostLogin(APlayerController* NewPlayer)
{
	if(PlayerListUpdate)
	{
		PlayerListUpdate->PostLogin(NewPlayer);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Emerald,
			TEXT("nullptr"));
	}
}
