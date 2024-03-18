// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameRoomInfoWidget.h"
#include "Components/TextBlock.h"


void UInGameRoomInfoWidget::InitSetText(const FString& Name, const FString& Code)
{
	NameText->SetText(FText::FromString(Name));
	CodeText->SetText(FText::FromString(Code));
}

void UInGameRoomInfoWidget::Show()
{
	PlayAnimationForward(InfoAnimation);

	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue,
	                                 FString::Printf(TEXT("룸 코드")));
}

void UInGameRoomInfoWidget::Hide()
{
	PlayAnimationReverse(InfoAnimation);
}
