// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
/**
 * 
 */
class CAPSTONE_2024_20_API IControlStrategy
{
public:
	virtual void Move(const FInputActionInstance& Instance, AActor* Actor, APlayerController* PlayerController, float DeltaTime) = 0;
	
};
