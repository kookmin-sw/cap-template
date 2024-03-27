#pragma once

#include "EnemyShip.generated.h"

class AMyShip;

UCLASS()
class AEnemyShip : public AActor
{
	GENERATED_BODY()
	
public:
	AEnemyShip();
	virtual void BeginPlay() override;
	
	void LookAtMyShip(const AMyShip* MyShip);
	void MoveToMyShip(const AMyShip* MyShip);

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
};
