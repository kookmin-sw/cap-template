// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameRoomInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_2024_20_API UInGameRoomInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void InitSetText(const FString& Name, const FString& Code);

	UFUNCTION()
	void Show();
	UFUNCTION()
	void Hide();
	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* NameText;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* CodeText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetAnimation* InfoAnimation;
};
