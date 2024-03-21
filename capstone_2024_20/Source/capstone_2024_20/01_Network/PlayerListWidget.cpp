// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerListWidget.h"

void UPlayerListWidget::Add(FString& NewName)
{
	GEngine->AddOnScreenDebugMessage(-1, 60.f,
	                                 FColor::Emerald, FString::Printf(TEXT("number: %d name: %s"), length, *NewName));
	PlayerElements[length]->SetInfo(FString::FromInt(length + 1), NewName);
	length += 1;
}

void UPlayerListWidget::Remove(int32 Index)
{
	PlayerElements[Index]->Clear();
	for (int i = Index; i < length-1; i++)
	{
		int32 Number = i + 1;
		FString Name = PlayerElements[Number]->GetName();

		PlayerElements[i]->SetInfo(FString::FromInt(Number), Name);
	}
	length -= 1;
}

int32 UPlayerListWidget::GetLength()
{
	return length;
}
