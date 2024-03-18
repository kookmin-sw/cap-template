// Fill out your copyright notice in the Description page of Project Settings.


#include "StageSelectController.h"

#include "MyUserWidget.h"

// Sets default values
AStageSelectController::AStageSelectController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootComponent);
}


// Called when the game starts or when spawned
void AStageSelectController::BeginPlay()
{
	Super::BeginPlay();
	ClickStageDelegate.AddDynamic(this, &AStageSelectController::MulticastRPC_ClickStage);
	ClickHideStageDelegate.AddDynamic(this, &AStageSelectController::MulticastRPC_HideStagePopupWidget);
	
	StageWidget = CreateWidget<UMyUserWidget>(GetWorld(), StageWidgetFactory);
	if (StageWidget)
	{
		StageWidget->AddToViewport();
		if (HasAuthority())
		{
			StageWidget->InitRPC(ClickStageDelegate, ClickHideStageDelegate);
		}
	}
}

// Called every frame
void AStageSelectController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStageSelectController::MulticastRPC_HideStagePopupWidget_Implementation()
{
	StageWidget->MyButtonClicked();
}

void AStageSelectController::ServerTravel()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->ServerTravel(FString("/Game/Level/level_1?listen"));
	}
}


void AStageSelectController::MulticastRPC_ClickStage_Implementation(int num)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow,
	                                 FString::Printf(TEXT("RPC전달")));

	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow,
		                                 FString::Printf(TEXT("난 서버 클릭 클릭 %d"), num));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow,
		                                 FString::Printf(TEXT("서버가 스테이지%d 버튼을 클릭함"), num));
	}

	UStageButton* StageButton = StageWidget->GetStageButton(num);
	UUserWidget* PopUpWidget = StageButton->CreatePopup();
	
	
	StageButton->GetStartButton()->OnClicked.AddDynamic(this, &AStageSelectController::ServerTravel);
}
