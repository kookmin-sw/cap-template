// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IControlStrategy.h"

/**
 * 
 */
class CAPSTONE_2024_20_API ShipControlStrategy : public IControlStrategy
{
public:
	virtual void Move(const FInputActionInstance& Instance, AActor* Actor, float DeltaTime) override;
	float MoveSpeed = 600.0f; // 선박의 전진 속도
	float CurrentRotationSpeed = 1.0f; // 현재 회전 속도, 초기값 1
	float MaxRotationSpeed = 10.0f; // 최대 회전 속도
	float RotationAcceleration = 1.0f; // 회전 가속도
	int LastInputDirection = 0; // 마지막 입력 방향, -1: 왼쪽, 0: 없음, 1: 오른쪽
};
