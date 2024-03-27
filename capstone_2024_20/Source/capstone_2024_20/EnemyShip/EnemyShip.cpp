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
}

void AEnemyShip::MoveToMyShip(const AMyShip* MyShip)
{
	const auto MyShipLocation = MyShip->GetActorLocation();
	const auto Direction = MyShipLocation - GetActorLocation();

	// Todo@autumn - This is a temporary solution, replace it with data.
	if (Direction.Size() < 4000.0f)
	{
		return;
	}
	
	const auto NormalizedDirection = Direction.GetSafeNormal();
	constexpr auto Speed = 2500.0f; // Todo@autumn - This is a temporary solution, replace it with data.
	const auto NewLocation = GetActorLocation() + NormalizedDirection * Speed * GetWorld()->DeltaTimeSeconds;
	SetActorLocation(NewLocation);
}
