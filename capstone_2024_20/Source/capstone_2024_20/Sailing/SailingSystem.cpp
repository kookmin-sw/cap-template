#include "SailingSystem.h"
#include "../EnemyShip/EnemyShip.h"
#include "../MyShip.h"
#include "Kismet/GameplayStatics.h"

ASailingSystem::ASailingSystem(): MyShip(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASailingSystem::BeginPlay()
{
	Super::BeginPlay();

	// To ensure that the ship is set before sailing system starts, run SetMyShip on world begin play
	GetWorld()->OnWorldBeginPlay.AddUObject(this, &ASailingSystem::SetMyShip);
}

// ReSharper disable once CppParameterMayBeConst
void ASailingSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnEnemyShipTimer += DeltaTime;

	// Run SpawnEnemyShip every 5 seconds
	// Todo@autumn - This is a temporary solution, replace it with data.
	if (SpawnEnemyShipTimer >= 5.0f)
	{
		SpawnEnemyShip();
		SpawnEnemyShipTimer = 0.0f;
	}

	for (const auto EnemyShip : EnemyShips)
	{
		EnemyShip->LookAtMyShip(MyShip);
		EnemyShip->MoveToMyShip(MyShip);
	}
}

void ASailingSystem::SpawnEnemyShip()
{
	// Spawn an enemy ship at a random location which is away between -20000 and 20000 units from the player, not in -10000 to 10000 units.
	// Todo@autumn - This is a temporary solution, replace it with data.
	auto RandomX = FMath::RandRange(-20000.0f, 20000.0f);
	auto RandomY = FMath::RandRange(-20000.0f, 20000.0f);

	RandomX = RandomX < 0 ? RandomX - 10000.0f : RandomX + 10000.0f;
	RandomY = RandomY < 0 ? RandomY - 10000.0f : RandomY + 10000.0f;
	
	const auto RandomLocation = FVector(RandomX, RandomY, 0.0f);
	AEnemyShip* SpawnedEnemyShip = GetWorld()->SpawnActor<AEnemyShip>(AEnemyShip::StaticClass(), FTransform(RandomLocation));
	EnemyShips.Add(SpawnedEnemyShip);
}

void ASailingSystem::SetMyShip()
{
	// Todo@autumn - This is a temporary solution, replace it.
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyShip::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		MyShip = Cast<AMyShip>(FoundActors[0]);
	}
}

