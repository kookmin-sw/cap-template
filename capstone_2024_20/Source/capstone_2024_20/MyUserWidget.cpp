// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"

bool UMyUserWidget::Initialize()
{
	Super::Initialize();

	for(int i=1; i<=BtnNum; i++)
	{
		FString ButtonName = FString::Printf(TEXT("StageButton%d"),i);
		UWidget* BtnWidget = GetWidgetFromName(*ButtonName);
		UStageButton* Button = Cast<UStageButton>(BtnWidget);

		if(i > ClearStage)
		{
			//Button->SetIsEnabled(false);
			Button->SetBackgroundColor(FColor::Red);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("button off"));
		}
		
		if(Button != nullptr)
		{
			Buttons.Add(Button);
			Button->OnClicked.AddDynamic(this, &UMyUserWidget::MyButtonClicked);
			Button->SetStageNum(i);
			Button->SettingStagePopUpWidget();
		}
	}
	return true;
}


void UMyUserWidget::MyButtonClicked()
{
	for(int i=0; i<BtnNum; i++)
	{
		Buttons[i]->HidePopUp();
	}

}
