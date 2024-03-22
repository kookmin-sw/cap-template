// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerListWidgetCreate.h"

#include "Blueprint/UserWidget.h"
#include "InGameRoomInfoWidget.h"
#include "PlayerListWidget.h"
#include "PlayerListWidgetModifier.h"
#include "Kismet/GameplayStatics.h"

PlayerListWidgetCreate::PlayerListWidgetCreate(UWorld* World, FString& WidgetName, UPlayerListWidget** PlayerListWidget, IPlayerList** PlayerList)
{
	CurrentWorld = World;
	PlayerListWidgetClass = WidgetName;
	ControllerPlayerListWidget = PlayerListWidget;
	ControllerPlayerList = PlayerList;
}

void PlayerListWidgetCreate::PostLogin(APlayerController* NewPlayer)
{
	UPlayerListWidget* PlayerListWidget = CreatePlayerListWidget();
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Emerald,
	                                 TEXT("Create PostLogin"));
	*ControllerPlayerList = new UPlayerListWidgetModifier(PlayerListWidget);
	(**ControllerPlayerList).PostLogin(NewPlayer);
	*ControllerPlayerListWidget = PlayerListWidget;
}

UPlayerListWidget* PlayerListWidgetCreate::CreatePlayerListWidget()
{
	FString Path = FString("/Game/WidgetBlueprints/" + PlayerListWidgetClass);

	UBlueprint* BlueprintObject = LoadObject<UBlueprint>(nullptr, *Path);

	UPlayerListWidget* WidgetInstance = nullptr;
	if (BlueprintObject)
	{
		UClass* GeneratedClass = BlueprintObject->GeneratedClass;
		if (GeneratedClass)
		{
			WidgetInstance = CreateWidget<UPlayerListWidget>(CurrentWorld, GeneratedClass);
			WidgetInstance->AddToViewport(100);
			
			GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Emerald,
											 TEXT("Create !!Success"));
		}
		return WidgetInstance;
	}
	return WidgetInstance;
}
