// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameModeBaseTest.h"

#include "InGameStateTest.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "capstone_2024_20/MyCharacter.h"
#include "capstone_2024_20/MyPlayerController.h"
#include "Interfaces/OnlineSessionInterface.h"

AInGameModeBaseTest::AInGameModeBaseTest()
{
	static ConstructorHelpers::FClassFinder<AMyCharacter> pawn(TEXT("/Game/BP/BP_MyCharacter"));
	DefaultPawnClass = pawn.Class;

	PlayerControllerClass = AMyPlayerController::StaticClass();
}

void AInGameModeBaseTest::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->InputComponent->BindKey(EKeys::C, IE_Pressed, this, &ThisClass::PrintRoomCode);
	}
	
}

void AInGameModeBaseTest::PrintRoomCode()
{
	FName RoomCode = GetGameState<AInGameStateTest>()->GetRoomCode();
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue,
								 FString::Printf(TEXT("룸 코드: %s"), *RoomCode.ToString()));

	UE_LOG(LogTemp, Warning, TEXT("Test"));
}
