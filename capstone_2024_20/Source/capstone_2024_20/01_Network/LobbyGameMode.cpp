// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "LobbyGameState.h"
#include "LobbyWidget.h"
#include "NetworkService.h"
#include "OnlineSessionSettings.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ListView.h"
#include "Kismet/GameplayStatics.h"

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(World, ANetworkService::StaticClass(), FoundActors);
	ANetworkService* NetworkService = nullptr;
	if (FoundActors.Num() > 0)
	{
		NetworkService = Cast<ANetworkService>(FoundActors[0]);
	}
	
	const ALobbyGameState *LobbyGameState = GetGameState<ALobbyGameState>();
	
	if(MainWidget != nullptr)
	{
		MainUI = CreateWidget<ULobbyWidget>(World, MainWidget);
		if(MainUI != nullptr)
		{
			MainUI->AddToViewport();
		}
	}

	MainUI->RoomNameTextBox->OnTextChanged.AddDynamic(LobbyGameState, &ALobbyGameState::SetRoomName);
	MainUI->RoomCodeTextBox->OnTextChanged.AddDynamic(LobbyGameState, &ALobbyGameState::SetRoomCode);
	MainUI->CreateButton->OnClicked.AddDynamic(NetworkService, &ANetworkService::CreateGameSession);
	MainUI->JoinRoomCodeButton->OnClicked.AddDynamic(NetworkService, &ANetworkService::JoinGameSession);
	MainUI->RefreshButton->OnClicked.AddDynamic(this, &ThisClass::OnClickRefreshButton);
	//OnClickRefreshButton();
}

void ALobbyGameMode::OnClickRefreshButton()
{
	ANetworkService* NetworkService = GetGameState<ALobbyGameState>()->NetworkService;
	NetworkService->AddFindSessionsCompleteDelegate(
		FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::RefreshRoomListUI));

	NetworkService->FindGameSession();
}

void ALobbyGameMode::RefreshRoomListUI(bool bWasSuccessful) const
{
	ANetworkService* NetworkService = GetGameState<ALobbyGameState>()->NetworkService;
	
	if (bWasSuccessful == false)
	{
		return;
	}

	MainUI->RoomListView->ClearListItems();
	MainUI->RefreshRoomList(NetworkService->GetSessionSearch()->SearchResults);
}
