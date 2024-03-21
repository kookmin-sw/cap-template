// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerListWidgetModifier.h"

#include "GameFramework/PlayerState.h"

UPlayerListWidgetModifier::UPlayerListWidgetModifier(UPlayerListWidget* NewPlayerListWidget)
{
	PlayerListWidget = NewPlayerListWidget;
}

void UPlayerListWidgetModifier::PostLogin(APlayerController* NewPlayer)
{
	APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
	if (PlayerState)
	{
		int32 Id = PlayerState->GetPlayerId();
		FString PlayerName = PlayerState->GetPlayerName();

		IdIndexMap.Add(Id, PlayerListWidget->GetLength());
		PlayerListWidget->Add(PlayerName);
	}
}

void UPlayerListWidgetModifier::Logout(AController* Exiting)
{
	APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>();
	int32 Id = PlayerState->GetPlayerId();
	int32* Index = IdIndexMap.Find(Id);

	PlayerListWidget->Remove(*Index);
}
