// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomListElement.h"

#include "NetworkService.h"
#include "RoomListElementData.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void URoomListElement::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	URoomListElementData* Data = Cast<URoomListElementData>(ListItemObject);
	RoomListElementData = Data;
	RoomName->SetText(RoomListElementData->RoomText);
	JoinButton->OnClicked.AddDynamic(this, &URoomListElement::OnClickJoin);
}

void URoomListElement::OnClickJoin()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("룸 입장 버튼 클릭 클릭 클릭!")));
	RoomListElementData->NetworkService->JoinRoomGameSession(RoomListElementData->Result);
}
