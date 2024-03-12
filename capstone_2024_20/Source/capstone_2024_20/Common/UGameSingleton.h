#pragma once

#include "UGameSingleton.generated.h"

UCLASS()
class CAPSTONE_2024_20_API UGameSingleton : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
	
public:
	UGameSingleton();

	virtual void Tick(float DeltaTime) override;
	
	static UGameSingleton& GetInstance();

	// [begin] FTickableGameObject
	virtual bool IsTickable() const override;
	virtual bool IsTickableInEditor() const override;
	virtual bool IsTickableWhenPaused() const override;
	virtual TStatId GetStatId() const override;
	virtual UWorld* GetWorld() const override;
	bool bTickable;
	bool bTickableWhenPaused;
	// [end] FTickableGameObject
};
