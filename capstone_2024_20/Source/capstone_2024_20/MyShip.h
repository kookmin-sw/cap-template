// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyShip.generated.h"

UCLASS()
class CAPSTONE_2024_20_API AMyShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(Category=Character, VisibleAnywhere)
	UStaticMeshComponent* M_MeshComponent;
	
};
