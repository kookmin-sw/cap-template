// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerListWidget.h"

void UPlayerListWidget::Add(FString& NewName)
{
	GEngine->AddOnScreenDebugMessage(-1, 60.f,
	                                 FColor::Emerald, FString::Printf(TEXT("number: %d name: %s"), length, *NewName));
	PlayerElements[length]->SetInfo(FString::FromInt(length+1), NewName);
	length += 1;
}
