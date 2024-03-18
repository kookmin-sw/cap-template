// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameStateTest.h"

#include "NetworkService.h"
#include "RoomData.h"
#include "Kismet/GameplayStatics.h"

void AInGameStateTest::BeginPlay()
{
	Super::BeginPlay();
}

FName AInGameStateTest::GetRoomCode() const
{
	return NetworkService->GetJoiningSessionSetting(RoomTEXT::CODE);
}

FName AInGameStateTest::GetRoomName() const
{
	return NetworkService->GetJoiningSessionSetting(RoomTEXT::NAME);
}
