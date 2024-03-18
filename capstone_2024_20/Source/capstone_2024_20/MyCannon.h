// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "MyCannon.generated.h"

UCLASS()
class CAPSTONE_2024_20_API AMyCannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyCannon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* M_ShooterMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UArrowComponent* ProjectileSpawnPoint;

	// 발사체의 클래스를 설정하기 위한 프로퍼티
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<class ACannonBall> ProjectileClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Effects")
	UParticleSystem* FireEffect;

	
	UFUNCTION()
	FVector GetCannonSpawnLocation();
	UFUNCTION()
	FRotator GetCannonSpawnRotation();

	UFUNCTION()
	void FireCannon();
};
