// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Containers/Array.h"
#include "OnlineSubsystemUtils.h"
#include "NetworkService.generated.h"

UCLASS()
class CAPSTONE_2024_20_API ANetworkService : public AActor
{
	GENERATED_BODY()

public:
	ANetworkService();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	IOnlineSessionPtr OnlineSessionInterface;

	UFUNCTION()
	void CreateGameSession();
	UFUNCTION()
	void FindGameSession();
	UFUNCTION()
	void JoinGameSession();
	void JoinRoomGameSession(FOnlineSessionSearchResult& Result) const;

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful) const;
	void OnFindSessionComplete(bool bWasSuccessful) const;
	void OnJoinSessionComplate(FName SessionName, EOnJoinSessionCompleteResult::Type Result) const;

	TSharedPtr<FOnlineSessionSearch>& GetSessionSearch();

	void AddFindSessionsCompleteDelegate(FOnFindSessionsCompleteDelegate NewFindSessionsCompleteDelegate);

private:
	TSharedPtr<FOnlineSessionSettings> GetSessionSettings();
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate FindSessionCompleteDelegate;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate FindSessionInitCompleteDelegate;

	bool bIsLan = false;

public:
	static FString CreateRoomCode();
};
