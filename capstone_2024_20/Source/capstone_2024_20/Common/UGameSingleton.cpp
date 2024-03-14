#include "UGameSingleton.h"

UGameSingleton::UGameSingleton()
{
}

// ReSharper disable once CppParameterMayBeConst
void UGameSingleton::Tick(float DeltaTime)
{
}

UGameSingleton& UGameSingleton::GetInstance()
{
	if (UGameSingleton* Instance = CastChecked<UGameSingleton>(GEngine->GameSingleton))
		return *Instance;

	return *NewObject<UGameSingleton>();
}
