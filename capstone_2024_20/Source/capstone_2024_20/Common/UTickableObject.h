#pragma once
#include "UTickableObject.generated.h"

UCLASS()
class CAPSTONE_2024_20_API UTickableObject : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
	
public:
	UTickableObject();

	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual bool IsTickableInEditor() const override;
	virtual bool IsTickableWhenPaused() const override;
	virtual TStatId GetStatId() const override;
	virtual UWorld* GetWorld() const override;
	
	bool bTickable;
	bool bTickableInEditor;
	bool bTickableWhenPaused;
};
