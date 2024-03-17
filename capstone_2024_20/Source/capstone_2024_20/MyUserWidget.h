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

	UFUNCTION(BlueprintCallable)
	void MyButtonClicked();

	int BtnNum=4;
	int ClearStage = 2;
	TArray<UStageButton*> Buttons;
	
public:
	void InitRPC(FMulticastRPC_ClickStageDelegate& ClickDelegate);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> StagePopUpWidgetClass;

	UPROPERTY(EditAnywhere)
	UUserWidget* CurrentWidget;

	void RegisterButtonClickHandler(FMulticastRPC_ClickStageDelegate& ClickStageDelegate);

	UStageButton* GetStageButton(int buttonNumber);
};
