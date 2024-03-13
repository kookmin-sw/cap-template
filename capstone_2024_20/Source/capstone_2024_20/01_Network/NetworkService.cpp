// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkService.h"

#include "LobbyGameState.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

#include "TimerManager.h"
#include "Online/OnlineSessionNames.h"

ANetworkService::ANetworkService()
	: CreateSessionCompleteDelegate(
		  FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete)),
	  FindSessionCompleteDelegate(
		  FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionComplete)),
	  JoinSessionCompleteDelegate(
		  FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplate))
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();
	}
}

void ANetworkService::BeginPlay()
{
	Super::BeginPlay();
	
	OnlineSessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);
	OnlineSessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);
}

void ANetworkService::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ANetworkService::CreateGameSession()
{
	if (OnlineSessionInterface.IsValid() == false)
	{
		return;
	}

	auto ExistingSession = OnlineSessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession != nullptr)
	{
		OnlineSessionInterface->DestroySession(NAME_GameSession);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Black,
			                                 FString::Printf(TEXT("삭제 session : %s"), NAME_GameSession));
		}
	}

	TSharedPtr<FOnlineSessionSettings> SessionSettings = GetSessionSettings();

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	OnlineSessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *SessionSettings);
}

void ANetworkService::FindGameSession()
{
	if (OnlineSessionInterface.IsValid() == false)
	{
		return;
	}

	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->MaxSearchResults = 5;
	SessionSearch->bIsLanQuery = bIsLan;
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	OnlineSessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), SessionSearch.ToSharedRef());
}

void ANetworkService::JoinGameSession()
{
	AddFindSessionsCompleteDelegate(FindSessionCompleteDelegate);
	FindGameSession();
}

void ANetworkService::JoinRoomGameSession(FOnlineSessionSearchResult& Result) const
{
	FString ResultRoomCode;
	Result.Session.SessionSettings.Get(RoomTEXT::NAME, ResultRoomCode);
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red,
	                                 FString::Printf(TEXT("룸 입장 버튼 클릭 클릭 클릭! %s"), *ResultRoomCode));

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	OnlineSessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, Result);
}

FName ANetworkService::GetJoiningSessionSetting(FName SettingName)
{
	FNamedOnlineSession* CurrentSession = OnlineSessionInterface->GetNamedSession(NAME_GameSession);
	if(CurrentSession)
	{
		FString SettingValue;
		CurrentSession->SessionSettings.Get(SettingName, SettingValue);
		return FName(SettingValue);
	}

	UE_LOG(LogTemp, Error, TEXT("Error: 세션 정보가 확인되지 않음 %s"), SettingName)
	return TEXT("Error");
}

void ANetworkService::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful) const
{
	if (bWasSuccessful == false)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("세션 생성 실패!")));
		}
		return;
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue,
		                                 FString::Printf(TEXT("세션 생성완료 : %s"), *SessionName.ToString()));
	}

	UWorld* World = GetWorld();
	if (World)
	{
		World->ServerTravel(FString("/Game/Level/level_1?listen"));
	}
}

void ANetworkService::OnFindSessionComplete(bool bWasSuccessful) const
{
	if (OnlineSessionInterface.IsValid() == false || bWasSuccessful == false)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue,
	                                 FString::Printf(TEXT("검색 준비")));

	const ALobbyGameState* LobbyGameState = GetWorld()->GetGameState<ALobbyGameState>();
	for (auto Result : SessionSearch->SearchResults)
	{
		FString MatchType;
		Result.Session.SessionSettings.Get(FName("MatchType"), MatchType);
	
		FString Id = Result.GetSessionIdStr();
		FString User = Result.Session.OwningUserName;

		FString RoomCode;
		Result.Session.SessionSettings.Get(FName("RoomCode"), RoomCode);

		if(RoomCode == LobbyGameState->RoomData.Code)
		{
			JoinRoomGameSession(Result);
		}
		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan,
			                                 FString::Printf(TEXT("Session ID : %s / Owner : %s"), *Id, *User));
		}
	}
}

void ANetworkService::OnJoinSessionComplate(FName SessionName, EOnJoinSessionCompleteResult::Type Result) const
{
	if (OnlineSessionInterface.IsValid() == false)
	{
		return;
	}

	FString Address;
	if (OnlineSessionInterface->GetResolvedConnectString(NAME_GameSession, Address))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow,
			                                 FString::Printf(TEXT("Connect String : %s"), *Address));
		}

		APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
		if (PlayerController)
		{
			PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
		}
	}
}

TSharedPtr<FOnlineSessionSearch>& ANetworkService::GetSessionSearch()
{
	return SessionSearch;
}

void ANetworkService::AddFindSessionsCompleteDelegate(FOnFindSessionsCompleteDelegate NewFindSessionsCompleteDelegate)
{
	OnlineSessionInterface->OnFindSessionsCompleteDelegates.Clear();
	OnlineSessionInterface->AddOnFindSessionsCompleteDelegate_Handle(NewFindSessionsCompleteDelegate);
}

TSharedPtr<FOnlineSessionSettings> ANetworkService::GetSessionSettings()
{
	TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());

	SessionSettings->bIsLANMatch = bIsLan;
	SessionSettings->NumPublicConnections = 4;
	SessionSettings->bAllowJoinInProgress = true;
	SessionSettings->bAllowJoinViaPresence = true;
	SessionSettings->bShouldAdvertise = true;
	SessionSettings->bUsesPresence = true;
	SessionSettings->bUseLobbiesIfAvailable = true;

	SessionSettings->Set(FName("MatchType"), FString("FreeForAll"),
	                     EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	if (const ALobbyGameState* LobbyGameState = GetWorld()->GetGameState<ALobbyGameState>())
	{
		FRoomData RoomData = LobbyGameState->RoomData;
		SessionSettings->Set(FName("RoomName"), RoomData.Name, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		RoomData.Code = ANetworkService::CreateRoomCode();
		SessionSettings->Set(FName("RoomCode"), RoomData.Code, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow,
		                                 FString::Printf(TEXT("RoomCode : %s"), *RoomData.Code));
	}


	return SessionSettings;
}

FString ANetworkService::CreateRoomCode()
{
	const FString Characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const int32 Length = 7;

	FString RandomString;

	for (int32 i = 0; i < Length; ++i)
	{
		int32 RandomIndex = FMath::RandRange(0, Characters.Len() - 1);
		RandomString.AppendChar(Characters[RandomIndex]);
	}

	return RandomString;
}
