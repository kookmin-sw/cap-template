// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReplicatedActor.generated.h"

UCLASS()
class CAPSTONE_2024_20_API AReplicatedActor : public AActor
{
	GENERATED_BODY()

public:
	AReplicatedActor();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated = OnRep_Location)
	FVector Location;

	UPROPERTY(ReplicatedUsing = OnRep_Rotation)
	FRotator Rotation;

	UFUNCTION()
	void OnRep_Location();
	UFUNCTION()
	void OnRep_Rotation();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
