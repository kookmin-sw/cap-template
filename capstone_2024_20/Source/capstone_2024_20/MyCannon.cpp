// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCannon.h"

#include "CannonBall.h"
#include "Kismet/GameplayStatics.h"
#include "Settings/LevelEditorPlayNetworkEmulationSettings.h"

// Sets default values
AMyCannon::AMyCannon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	// Arrow 컴포넌트 생성 및 설정
}

// Called when the game starts or when spawned
void AMyCannon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyCannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AMyCannon::GetCannonSpawnLocation()
{
	return ProjectileSpawnPoint->GetComponentLocation();
}

FRotator AMyCannon::GetCannonSpawnRotation()
{
	return ProjectileSpawnPoint->GetComponentRotation();
}

void AMyCannon::FireCannon()
{
	MultiCastRPC_FireCannon();
}

void AMyCannon::MultiCastRPC_FireCannon_Implementation()
{
	// 발사 위치와 방향 설정

	// 발사체 생성
	if (HasAuthority())
	{
		GetWorld()->SpawnActor<ACannonBall>(ProjectileClass, GetCannonSpawnLocation(), GetCannonSpawnRotation());
	}

	if (FireEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireEffect, GetCannonSpawnLocation(),
												 GetCannonSpawnRotation());
	}
	// 발사체에 추가적인 로직이 필요하면 여기에 작성
}
