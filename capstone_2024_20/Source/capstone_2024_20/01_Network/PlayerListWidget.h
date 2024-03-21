// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerListElementWidget.h"
#include "Blueprint/UserWidget.h"
#include "PlayerListWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_2024_20_API UPlayerListWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UPlayerListElementWidget*> PlayerElements;

	void Add(FString& NewName);
	void Remove(int32 Index);
	int32 GetLength();
private:
	int32 length = 0;
};
