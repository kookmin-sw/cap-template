// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StageSelectController.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "StageButton.generated.h"

/**
 * 
 */
UCLASS()

class CAPSTONE_2024_20_API UStageButton : public UButton
{
	GENERATED_BODY()
	
	int StageNum;
	UUserWidget* StagePopUpWidget;
	UTextBlock* stage_text;
	UButton* start_btn;
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> StagePopUpWidgetClass;
	

	
public:
	FMulticastRPC_ClickStageDelegate OnCLickButton;
	
	UFUNCTION()
	void SettingStagePopUpWidget();
	

	UFUNCTION()
	void SetStageNum(int Num);

	UFUNCTION()
	void OnClickButton();

	UFUNCTION()
	void HidePopUp();

	UFUNCTION()
	void Stage_Start();

	UFUNCTION()
	UUserWidget* CreatePopup();

	UFUNCTION()
	UButton* GetStartButton();
};
