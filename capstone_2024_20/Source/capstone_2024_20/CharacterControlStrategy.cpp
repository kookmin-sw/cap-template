// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterControlStrategy.h"

#include "MyCharacter.h"

void CharacterControlStrategy::Move(const FInputActionInstance& Instance, AActor* Actor,APlayerController* PlayerController, float DeltaTime)
{
	AMyCharacter* Character = Cast<AMyCharacter>(Actor);
	if (Character)
	{
		FVector2D MoveVec = Instance.GetValue().Get<FVector2D>();

		const FRotator Rotation = Character->GetControlRotation();
		const FRotator YawRotation(0,Rotation.Yaw,0);
		const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		Character->AddMovementInput(ForwardDir, MoveVec.Y);
		Character->AddMovementInput(RightDir, MoveVec.X);
	}
}
