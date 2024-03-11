// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
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

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

private:
	UPROPERTY(Category=Input, VisibleAnywhere)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(Category=Input, VisibleAnywhere)
	UInputAction* MoveAction;

	UPROPERTY(Category=Input, VisibleAnywhere)
	UInputAction* InteractionAction;

public:
	UPROPERTY(Category=UI, VisibleAnywhere)
	class UWidgetComponent* TextWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APawn* Ship;

	AMyCharacter* Player;

protected:
	void Move(const FInputActionInstance& Instance);
	void Interaction(const FInputActionInstance& Instance);

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

	
};
