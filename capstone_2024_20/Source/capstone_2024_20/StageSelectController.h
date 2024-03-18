// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StageSelectController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMulticastRPC_ClickStageDelegate, int, Num);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMulticastRPC_HideStagePopupWidget);

UCLASS()
class CAPSTONE_2024_20_API AStageSelectController : public AActor
{
	GENERATED_BODY()

public:
	AStageSelectController();

private:
	class UMyUserWidget* StageWidget;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMyUserWidget> StageWidgetFactory;


	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPC_ClickStage(int num);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPC_HideStagePopupWidget();

	FMulticastRPC_ClickStageDelegate ClickStageDelegate;
	FMulticastRPC_HideStagePopupWidget ClickHideStageDelegate;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> StagePopUpWidgetClass;

	UFUNCTION()
	void ServerTravel();
};
