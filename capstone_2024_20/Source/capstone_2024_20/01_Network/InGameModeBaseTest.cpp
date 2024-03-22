// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameModeBaseTest.h"

#include "InGameRoomInfoWidget.h"
#include "InGameStateTest.h"
#include "NetworkService.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "capstone_2024_20/MyCharacter.h"
#include "capstone_2024_20/MyPlayerController.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Kismet/GameplayStatics.h"

AInGameModeBaseTest::AInGameModeBaseTest()
{
	static ConstructorHelpers::FClassFinder<AMyCharacter> pawn(TEXT("/Game/Blueprints/BP_MyCharacter"));
	DefaultPawnClass = pawn.Class;

	PlayerControllerClass = AMyPlayerController::StaticClass();
}

void AInGameModeBaseTest::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(World, ANetworkService::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		AInGameStateTest* InGameStateTest = GetGameState<AInGameStateTest>();
		InGameStateTest->NetworkService = Cast<ANetworkService>(FoundActors[0]);
	}
	
	RoomInfoWidget = CreateWidget<UInGameRoomInfoWidget>(GetWorld(), RoomInfoWidgetFactory);
	RoomInfoWidget->AddToViewport();

	const FString RoomCode = GetGameState<AInGameStateTest>()->GetRoomCode().ToString();
	const FString RoomName = GetGameState<AInGameStateTest>()->GetRoomName().ToString();
	RoomInfoWidget->InitSetText(RoomName, RoomCode);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->InputComponent->BindKey(EKeys::C, IE_Pressed, RoomInfoWidget, &UInGameRoomInfoWidget::Show);
		PlayerController->InputComponent->BindKey(EKeys::C, IE_Released, RoomInfoWidget, &UInGameRoomInfoWidget::Hide);
	}
}

void AInGameModeBaseTest::PrintRoomCode()
{
	const FName RoomCode = GetGameState<AInGameStateTest>()->GetRoomCode();
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue,
								 FString::Printf(TEXT("룸 코드: %s"), *RoomCode.ToString()));

	UE_LOG(LogTemp, Warning, TEXT("Test"));
}
