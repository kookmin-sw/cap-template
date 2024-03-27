#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SailingSystem.generated.h"

class AMyShip;
class AEnemyShip;
class AEvent;

UCLASS()
class CAPSTONE_2024_20_API ASailingSystem : public AActor
{
	GENERATED_BODY()

public:
	ASailingSystem();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SpawnEnemyShip();
	void SpawnEvent();
	
	void SetMyShip();

private:
	inline static float SpawnEnemyShipTimer = 0.0f;
	TArray<AEnemyShip*> EnemyShips;

	inline static float SpawnEventTimer = 0.0f;
	TArray<AEvent*> Events;

	UPROPERTY()
	AMyShip* MyShip;
};
