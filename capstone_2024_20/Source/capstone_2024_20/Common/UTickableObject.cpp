#include "UTickableObject.h"

UTickableObject::UTickableObject(): bTickable(true), bTickableInEditor(false), bTickableWhenPaused(false)
{
}

void UTickableObject::Tick(float DeltaTime)
{
	// do nothing
}

bool UTickableObject::IsTickable() const
{
	return bTickable;
}

bool UTickableObject::IsTickableInEditor() const
{
	return bTickableInEditor;
}

bool UTickableObject::IsTickableWhenPaused() const
{
	return bTickableWhenPaused;
}

TStatId UTickableObject::GetStatId() const
{
	return TStatId();
}

UWorld* UTickableObject::GetWorld() const
{
	return GetOuter()->GetWorld();
}