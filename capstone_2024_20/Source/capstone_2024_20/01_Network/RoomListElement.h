// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "RoomListElement.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_2024_20_API URoomListElement : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UTextBlock* RoomName;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton* JoinButton;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
	class URoomListElementData* RoomListElementData;

public:
	UFUNCTION()
	void OnClickJoin();
};
