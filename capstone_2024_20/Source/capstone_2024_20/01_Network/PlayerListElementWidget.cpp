// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerListElementWidget.h"

#include "Components/TextBlock.h"

void UPlayerListElementWidget::SetInfo(const FString& NewNumber, const FString& NewName)
{
	Number->SetText(FText::FromString(NewNumber));
	Name->SetText(FText::FromString(NewName));
}
