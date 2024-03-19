// Fill out your copyright notice in the Description page of Project Settings.


#include "ReplicatedActor.h"

#include "Net/UnrealNetwork.h"

// Sets default values
AReplicatedActor::AReplicatedActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootComponent);
}

void AReplicatedActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AReplicatedActor, Location);
	DOREPLIFETIME(AReplicatedActor, Rotation);
}

void AReplicatedActor::OnRep_Location()
{
	if (HasAuthority())
	{
		Location = GetActorLocation();
	}
	else
	{
		SetActorLocation(Location);
	}
}

void AReplicatedActor::OnRep_Rotation()
{
	if (HasAuthority())
	{
		Rotation = GetActorRotation();
	}
	else
	{
		SetActorRotation(Rotation);
	}
}

// Called when the game starts or when spawned
void AReplicatedActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AReplicatedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
