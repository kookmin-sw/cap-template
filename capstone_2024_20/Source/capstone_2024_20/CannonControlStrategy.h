// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IControlStrategy.h"

/**
 * 
 */
class CAPSTONE_2024_20_API CannonControlStrategy : public IControlStrategy
{
public:
	virtual void Move(const FInputActionInstance& Instance, AActor* Actor, float DeltaTime) override;
};
