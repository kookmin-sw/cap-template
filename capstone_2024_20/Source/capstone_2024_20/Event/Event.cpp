#include "Event.h"

AEvent::AEvent(): StaticMesh(nullptr)
{
	// TODO@autumn - This is a temporary mesh, replace it with the actual mesh from data
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Game/GameObjects/Wood/wood_mesh.wood_mesh'")));
	RootComponent = StaticMesh;
}

void AEvent::BeginPlay()
{
	Super::BeginPlay();
}
