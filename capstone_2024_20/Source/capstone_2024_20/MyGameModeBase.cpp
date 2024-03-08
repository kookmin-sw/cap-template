// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

#include "MyCharacter.h"
#include "MyPlayerController.h"

AMyGameModeBase::AMyGameModeBase()
{
	//DefaultPawnClass = AMyCharacter::StaticClass();
	static ConstructorHelpers::FClassFinder<AMyCharacter> pawn(TEXT("/Game/BP/BP_MyCharacter"));
	DefaultPawnClass = pawn.Class;
	
	PlayerControllerClass = AMyPlayerController::StaticClass();
}


void AMyGameModeBase::StartPlay()
{
	Super::StartPlay();

}
