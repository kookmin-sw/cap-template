#include "UGameSingleton.h"

UGameSingleton::UGameSingleton(): bTickable(true), bTickableWhenPaused(false)
{
}

void UGameSingleton::Tick(float DeltaTime)
{
}

UGameSingleton& UGameSingleton::GetInstance()
{
	if (UGameSingleton* Instance = CastChecked<UGameSingleton>(GEngine->GameSingleton))
		return *Instance;

	return *NewObject<UGameSingleton>();
}

// [begin] FTickableGameObject
bool UGameSingleton::IsTickable() const
{
	return bTickable;
}

bool UGameSingleton::IsTickableInEditor() const
{
	return bTickable;
}

bool UGameSingleton::IsTickableWhenPaused() const
{
	return bTickableWhenPaused;
}

TStatId UGameSingleton::GetStatId() const
{
	return TStatId();
}

UWorld* UGameSingleton::GetWorld() const
{
	return GetOuter()->GetWorld();
}
// [end] FTickableGameObject
