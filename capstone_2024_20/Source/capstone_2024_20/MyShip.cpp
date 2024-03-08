// Fill out your copyright notice in the Description page of Project Settings.


#include "MyShip.h"

#include "GameFramework/PawnMovementComponent.h"

// Sets default values
AMyShip::AMyShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	M_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = M_MeshComponent;


	// static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	//
	// M_MeshComponent->SetStaticMesh(Mesh.Object);
	// M_MeshComponent->SetRelativeLocation(FVector(-40.0f,-80.0f,0.0f));
	// M_MeshComponent->SetRelativeScale3D(FVector(8.0f, 18.5f, 1.0f));
}

// Called when the game starts or when spawned
void AMyShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

