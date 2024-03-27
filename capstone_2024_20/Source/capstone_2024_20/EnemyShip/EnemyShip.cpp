#include "EnemyShip.h"
#include "../MyShip.h"

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

void AEnemyShip::LookAtMyShip(const AMyShip* MyShip)
{
	const auto Direction = MyShip->GetActorLocation() - GetActorLocation();
	const auto Rotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	SetActorRotation(Rotation);

	UE_LOG(LogTemp, Warning, TEXT("EnemyShip %s is looking at MyShip %s, Direction: %s"), *GetName(), *MyShip->GetName(), *Direction.ToString());
}
