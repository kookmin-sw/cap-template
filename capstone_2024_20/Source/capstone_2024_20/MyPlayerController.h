// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IControlStrategy.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "MyCannon.h"
#include "CannonBall.h"
#include "MyCharacter.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_2024_20_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AMyPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
public:	
	// Called to bind functionality to input
	virtual void SetupInputComponent(class UInputComponent* PlayerInputComponent);

private:
	UPROPERTY(Category=Input, VisibleAnywhere)
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(Category=Input, VisibleAnywhere)
	UInputMappingContext* CannonMappingContext;

	UPROPERTY(Category=Input, VisibleAnywhere)
	UInputAction* MoveAction;

	UPROPERTY(Category=Input, VisibleAnywhere)
	UInputAction* InteractionAction;
	
	UPROPERTY(Category=Input, VisibleAnywhere)
	UInputAction* ShootAction;
public:
	UPROPERTY(Category=UI, VisibleAnywhere)
	class UWidgetComponent* TextWidget;

private:
	AActor* ControlledActor;
	IControlStrategy* CurrentStrategy;
	APawn* Ship;
	AMyCharacter* Player;
	AMyCannon* Cannon;
	UEnhancedInputLocalPlayerSubsystem* Subsystem;
	UInputMappingContext* LastMappingContext;

public:
	void Move(const FInputActionInstance& Instance);
    void Interaction(const FInputActionInstance& Instance);
    void Shoot(const FInputActionInstance& Instance);
	
	UFUNCTION(Server, Reliable)
	void ServerRPC_Shoot(AMyCannon* CannonActor);

	UFUNCTION(Server, Reliable)
	void ServerRPC_MoveCannon(AMyCannon* CannonActor, FRotator newRot);
	
protected:
	
	enum class ControlMode
	{
		CHARACTER,
		SHIP,
		CANNON
	};
	
	void SetControlMode(ControlMode NewControlMode);
	ControlMode CurrentControlMode=ControlMode::CHARACTER;
	void ViewChange();

	float TargetArmLength;
	FRotator TargetRotation;
	float ChangeSpeed = 5.0f;

	bool flag = true;
	
	
};
