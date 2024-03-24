#pragma once

#include "EnemyShip.generated.h"

UCLASS()
class AEnemyShip : public AActor
{
	GENERATED_BODY()
	
public:
	AEnemyShip();
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
};
