// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameStateTest.h"

#include "NetworkService.h"
#include "RoomData.h"
#include "Kismet/GameplayStatics.h"

void AInGameStateTest::BeginPlay()
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

FName AInGameStateTest::GetRoomCode() const
{
	return NetworkService->GetJoiningSessionSetting(RoomTEXT::CODE);
}
