#include "EnemyShip.h"

AEnemyShip::AEnemyShip(): StaticMesh(nullptr)
{
	// TODO@autumn - This is a temporary mesh, replace it with the actual mesh from data
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Game/GameObjects/FlatShip/Ship_Ship.Ship_Ship'")));
	RootComponent = StaticMesh;
}

void AEnemyShip::BeginPlay()
{
	Super::BeginPlay();
}
