// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkService.h"
#include "RoomData.h"
#include "GameFramework/GameStateBase.h"
#include "LobbyGameState.generated.h"

UCLASS()
class CAPSTONE_2024_20_API ALobbyGameState : public AGameStateBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void Init(ANetworkService* NewNetworkService);
	
	UPROPERTY(EditAnywhere, Category="Network")
	ANetworkService* NetworkService;
	
	UPROPERTY(EditAnywhere, Category = "Room")
	FRoomData RoomData;
	
	UFUNCTION(BlueprintCallable)
	void SetRoomData(const FRoomData& NewRoomData);

	UFUNCTION()
	void SetRoomName(const FText& RoomName);

	UFUNCTION()
	void SetRoomCode(const FText& RoomCode);
};
