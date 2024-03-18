// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"

#include "StageSelectController.h"

bool UMyUserWidget::Initialize()
{
	Super::Initialize();
	for (int i = 1; i <= BtnNum; i++)
	{
		FString ButtonName = FString::Printf(TEXT("StageButton%d"), i);
		UWidget* BtnWidget = GetWidgetFromName(*ButtonName);
		UStageButton* Button = Cast<UStageButton>(BtnWidget);

		if (i > ClearStage)
		{
			//Button->SetIsEnabled(false);
			Button->SetBackgroundColor(FColor::Red);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("button off"));
		}
		if (Button != nullptr)
		{
			Buttons.Add(Button);
			Button->SetStageNum(i);
			Button->SettingStagePopUpWidget();
		}
	}

	return true;
}


void UMyUserWidget::MyButtonClicked()
{
	for (int i = 0; i < BtnNum; i++)
	{
		Buttons[i]->HidePopUp();
	}
}

void UMyUserWidget::InitRPC(FMulticastRPC_ClickStageDelegate& ClickDelegate,
                            FMulticastRPC_HideStagePopupWidget& ClickHideStageDelegate)
{
	HideStageDelegate = ClickHideStageDelegate;
	RegisterButtonClickHandler(ClickDelegate, ClickHideStageDelegate);
}

void UMyUserWidget::RegisterButtonClickHandler(FMulticastRPC_ClickStageDelegate& ClickStageDelegate,
                                               FMulticastRPC_HideStagePopupWidget& ClickHideStageDelegate)
{
	BackgroundBtn->OnClicked.AddDynamic(this, &ThisClass::OnClickHideStage);
	for (int i = 0; i < BtnNum; i++)
	{
		Buttons[i]->OnClickHideButton = ClickHideStageDelegate;
		Buttons[i]->OnCLickButton = ClickStageDelegate;
	}
}

UStageButton* UMyUserWidget::GetStageButton(int buttonNumber)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow,
	                                 FString::Printf(TEXT("return button")));

	return Buttons[buttonNumber - 1];
}


void UMyUserWidget::OnClickHideStage()
{
	HideStageDelegate.Broadcast();
}
