// Fill out your copyright notice in the Description page of Project Settings.


#include "StageGameMode.h"
#include "StageSelectController.h"
#include "01_Network/PlayerListController.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

void AStageGameMode::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow,
	                                 FString(TEXT("Init진출")));

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStageSelectController::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		StageSelectController = Cast<AStageSelectController>(FoundActors[0]);
	}
}

void AStageGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
    	                                 TEXT("LOGOUT"));

	PlayerListController->Logout(Exiting);
}

void AStageGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	PlayerListController->PostLogin(NewPlayer);
	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Emerald,
	                                 TEXT("POST LOGIN"));


	FString Name = NewPlayer->PlayerState->GetPlayerName();
	int32 Id = NewPlayer->PlayerState->GetPlayerId();
	
	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Emerald,
									 FString::Printf(TEXT("name: %s, id: %d"), *Name, Id));
}
