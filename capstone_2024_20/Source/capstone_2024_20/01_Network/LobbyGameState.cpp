// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameState.h"

#include "NetworkService.h"
#include "Kismet/GameplayStatics.h"

void ALobbyGameState::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(World, ANetworkService::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		NetworkService = Cast<ANetworkService>(FoundActors[0]);
	}
}

void ALobbyGameState::Init(ANetworkService* NewNetworkService)
{
	NetworkService = NewNetworkService;
}

void ALobbyGameState::SetRoomData(const FRoomData& NewRoomData)
{
	RoomData = NewRoomData;
}

void ALobbyGameState::SetRoomName(const FText& RoomName)
{
	RoomData.Name = RoomName.ToString();
}

void ALobbyGameState::SetRoomCode(const FText& RoomCode)
{
	RoomData.Code = RoomCode.ToString();
}
