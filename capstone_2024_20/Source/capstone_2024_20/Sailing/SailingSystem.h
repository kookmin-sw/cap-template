#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SailingSystem.generated.h"

class AMyShip;
class AEnemyShip;

UCLASS()
class CAPSTONE_2024_20_API ASailingSystem : public AActor
{
	GENERATED_BODY()

public:
	ASailingSystem();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SpawnEnemyShip();
	void SetMyShip();

private:
	inline static float SpawnEnemyShipTimer = 0.0f;
	TArray<AEnemyShip*> EnemyShips;

	UPROPERTY()
	AMyShip* MyShip;
};
