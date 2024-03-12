// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionDelegates.h"
#include "LobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_2024_20_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UEditableTextBox* RoomNameTextBox;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UEditableTextBox* RoomCodeTextBox;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton* CreateButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton* JoinRoomCodeButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton* RefreshButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UListView* RoomListView;

	void RefreshRoomList(TArray<FOnlineSessionSearchResult>& RoomResults) const;

private:
	UFUNCTION()
	void ChangeRoomCodeTextBoxUpper(const FText& InText);
};
