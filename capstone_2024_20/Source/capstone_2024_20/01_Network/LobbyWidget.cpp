// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"

#include "LobbyGameMode.h"
#include "LobbyGameState.h"
#include "OnlineSessionSettings.h"
#include "RoomListElementData.h"
#include "Components/EditableTextBox.h"
#include "Components/ListView.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	RoomCodeTextBox->OnTextChanged.AddDynamic(this, &ThisClass::ChangeRoomCodeTextBoxUpper);
}

void ULobbyWidget::RefreshRoomList(TArray<FOnlineSessionSearchResult>& RoomResults) const
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("UI업데이트 시작")));
	}
	if (RoomResults.Num() == 0)
		return;

	for (const FOnlineSessionSearchResult& Room : RoomResults)
	{
		FString ResultRoomCode;
		Room.Session.SessionSettings.Get(FName("RoomCode"), ResultRoomCode);
		FString ResultRoomName;
		Room.Session.SessionSettings.Get(FName("RoomName"), ResultRoomName);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan,
			                                 FString::Printf(TEXT("RoomCode: %s"), *ResultRoomCode));
		}

		//FText RoomText = FText::FromString(TEXT("%s"),ResultRoomName);
		FText RoomText = FText::Format(FText::FromString(TEXT("{0}")), FText::FromString(ResultRoomName));

		URoomListElementData* RoomListData = NewObject<URoomListElementData>();
		RoomListData->Result = Room;
		if (const ALobbyGameState* LobbyGameState = GetWorld()->GetGameState<ALobbyGameState>())
		{
			RoomListData->NetworkService = LobbyGameState->NetworkService;
		}
		RoomListData->SetRoomName(RoomText);
		RoomListView->AddItem(RoomListData);
	}
}

void ULobbyWidget::ChangeRoomCodeTextBoxUpper(const FText& InText)
{
	RoomCodeTextBox->SetText(InText.ToUpper());
}
