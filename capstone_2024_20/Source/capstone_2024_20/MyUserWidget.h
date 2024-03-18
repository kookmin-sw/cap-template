// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StageButton.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class CAPSTONE_2024_20_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	virtual bool Initialize() override;

	int BtnNum=4;
	int ClearStage = 2;
	TArray<UStageButton*> Buttons;

	UPROPERTY(meta=(BindWidget))
	UButton* BackgroundBtn;
	
	FMulticastRPC_HideStagePopupWidget HideStageDelegate;
	UFUNCTION()
	void OnClickHideStage();
public:
	void InitRPC(FMulticastRPC_ClickStageDelegate& ClickDelegate, FMulticastRPC_HideStagePopupWidget& ClickHideStageDelegate);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> StagePopUpWidgetClass;

	UPROPERTY(EditAnywhere)
	UUserWidget* CurrentWidget;
	
	UFUNCTION(BlueprintCallable)
	void MyButtonClicked();
	
	void RegisterButtonClickHandler(FMulticastRPC_ClickStageDelegate& ClickStageDelegate, FMulticastRPC_HideStagePopupWidget& ClickHideStageDelegate);

	UStageButton* GetStageButton(int buttonNumber);
};
