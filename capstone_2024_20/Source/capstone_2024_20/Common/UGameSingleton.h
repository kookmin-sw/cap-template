#pragma once
#include "UTickableObject.h"
#include "UGameSingleton.generated.h"

UCLASS()
class CAPSTONE_2024_20_API UGameSingleton : public UTickableObject
{
	GENERATED_BODY()
	
public:
	UGameSingleton();
	
	virtual void Tick(float DeltaTime) override;
	static UGameSingleton& GetInstance();
};
