// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipControlStrategy.h"

#include "MyShip.h"

void ShipControlStrategy::Move(const FInputActionInstance& Instance, AActor* Actor,APlayerController* PlayerController, float DeltaTime)
{
	AMyShip* Ship = Cast<AMyShip>(Actor);
	if (Ship)
	{
		FVector2D MoveVec = Instance.GetValue().Get<FVector2D>();
		
		if(MoveVec.Y > 0)
		{
			FVector ForwardDirection = Ship->GetActorForwardVector();
			Ship->AddActorWorldOffset(-ForwardDirection * MoveVec.Y * MoveSpeed * DeltaTime, true);
		
			if(MoveVec.X != 0)
			{
				int InputDirection = 0;
				// 입력 방향을 결정합니다 (-1, 1)
				if(MoveVec.X > 0)
					InputDirection = 1;
				else
					InputDirection = -1;

				
				// 입력 방향이 마지막과 같은 경우, 회전 속도를 증가시킵니다.
				if( InputDirection == LastInputDirection)
				{
					CurrentRotationSpeed = FMath::Min(CurrentRotationSpeed + RotationAcceleration * DeltaTime, MaxRotationSpeed);
				}
				else
				{
					// 입력 방향이 바뀌었거나 첫 입력인 경우, 회전 속도를 초기화합니다.
					CurrentRotationSpeed = 1.0f;
				}	
				// 회전 처리를 합니다.
				FRotator CurrentRotation = Ship->GetActorRotation();
				float TargetYaw = CurrentRotation.Yaw + MoveVec.X * CurrentRotationSpeed * DeltaTime;
				Ship->SetActorRotation(FRotator(0.0f, TargetYaw, 0.0f));

				// 마지막 입력 방향을 업데이트합니다.
				LastInputDirection = InputDirection;
			}
			else
			{
				// 입력이 없을 경우, 회전 속도와 마지막 입력 방향을 초기화합니다.
				CurrentRotationSpeed = 1.0f;
				LastInputDirection = 0;
			}
		}
		
		
		
	}
}
