// Fill out your copyright notice in the Description page of Project Settings.


#include "StageGameMode.h"

#include "Blueprint/UserWidget.h"
#include "MyUserWidget.h"
#include "StageSelectController.h"
#include "01_Network/PlayerListController.h"
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

void AStageGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	PlayerListController->PostLogin(NewPlayer);
	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Emerald,
		TEXT("POST LOGIN"));
	//PlayerListController->PostLogin(NewPlayer);
}
