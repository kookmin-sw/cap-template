// Fill out your copyright notice in the Description page of Project Settings.


#include "CannonControlStrategy.h"

#include "MyCannon.h"
#include "MyPlayerController.h"

void CannonControlStrategy::Move(const FInputActionInstance& Instance, AActor* Actor,APlayerController* PlayerController, float DeltaTime)
{
	AMyCannon* Cannon = Cast<AMyCannon>(Actor);
	if (Cannon)
	{
		FVector2D MoveVec = Instance.GetValue().Get<FVector2D>();
		float RotationSpeed = 10.0f;

		const FRotator CurrentRotation = Cannon->M_ShooterMesh->GetRelativeRotation();
		float NewYaw = CurrentRotation.Yaw + (MoveVec.X * RotationSpeed * DeltaTime);

		// 새로운 회전 값을 설정합니다.
		FRotator NewRotation = FRotator(CurrentRotation.Pitch, NewYaw, CurrentRotation.Roll);
		//Cannon->M_ShooterMesh->SetRelativeRotation(NewRotation);

		AMyPlayerController* Controller = Cast<AMyPlayerController>(PlayerController);
		Controller->ServerRPC_MoveCannon(Cannon, NewRotation);
		
		
	}
}

