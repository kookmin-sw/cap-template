// Fill out your copyright notice in the Description page of Project Settings.


#include "StageButton.h"

#include "Kismet/GameplayStatics.h"

void UStageButton::SetStageNum(int Num)
{
	StageNum = Num;
}

void UStageButton::SettingStagePopUpWidget()
{
	//버튼 함수 연결
	this->OnClicked.AddDynamic(this, &UStageButton::OnClickButton);
	StagePopUpWidgetClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr,
		TEXT("/Game/UMG/StagePopUpWidget.StagePopUpWidget_C"));
	if(StagePopUpWidgetClass != nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("aaa"));
}



void UStageButton::OnClickButton()
{
	OnCLickButton.Broadcast(StageNum);
}

void UStageButton::HidePopUp()
{
	if(StagePopUpWidget != nullptr)
	{
		StagePopUpWidget->RemoveFromParent();
		StagePopUpWidget = nullptr;
	}
}

void UStageButton::Stage_Start()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Ahoi-!"));
	UGameplayStatics::OpenLevel(this, TEXT("level_1"));
}

UUserWidget* UStageButton::CreatePopup()
{
	//팝업 위젯 생성
	UUserWidget* PopUpWidget = CreateWidget<UUserWidget>(GetWorld(), StagePopUpWidgetClass);
	if(PopUpWidget != nullptr)
	{
		//팝업 위젯 배치
		PopUpWidget->AddToViewport();
		FVector2D pos = GetCachedGeometry().GetAbsolutePosition();
		PopUpWidget->SetPositionInViewport(FVector2D(pos.X - 30.0f, pos.Y - 200.0f));
		StagePopUpWidget = PopUpWidget;
	
		//텍스트 연동
		UWidget* textWidget = PopUpWidget->GetWidgetFromName(TEXT("Text_Stage"));
		stage_text = Cast<UTextBlock>(textWidget);
		
		if(stage_text != nullptr)
		{
			stage_text->SetText(FText::FromString(FString::Printf(TEXT("STAGE %d"), StageNum)));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Text_Stage widget not found or is not a UTextBlock."));
		}
	
		//버튼 연동
		UWidget* btnWidget = PopUpWidget->GetWidgetFromName(TEXT("Button_Start"));
		start_btn = Cast<UButton>(btnWidget);
	
		if(this->GetBackgroundColor() == FColor::Red)
		{
			start_btn->SetIsEnabled(false);
		}
	}

	return PopUpWidget;
}

UButton* UStageButton::GetStartButton()
{
	return start_btn;
}


