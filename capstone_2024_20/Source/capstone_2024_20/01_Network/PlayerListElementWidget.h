// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerListElementWidget.generated.h"

/**
 * 
 */
class UTextBlock;
UCLASS()
class CAPSTONE_2024_20_API UPlayerListElementWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Number;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Name;

	void SetInfo(const FString& NewNumber, const FString& NewName);
	void Clear();

	FString& GetName();
};
