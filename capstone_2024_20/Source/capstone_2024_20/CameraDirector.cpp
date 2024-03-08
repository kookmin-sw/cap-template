// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeToNextCameraChange -= DeltaTime;
	if (TimeToNextCameraChange <= 0.0f)
	{
		constexpr float ChangeTime = 3.0f;
     	
		TimeToNextCameraChange += ChangeTime;
		APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
		
		if (Controller)
		{	
			constexpr float BlendTime = 0.75f;
			if (Controller->GetViewTarget() != CameraOne && CameraOne != nullptr)
			{
				Controller->SetViewTargetWithBlend(CameraOne, BlendTime);
			}
			else if (Controller->GetViewTarget() != CameraTwo && CameraTwo != nullptr)
			{
				Controller->SetViewTargetWithBlend(CameraTwo, BlendTime);
			}
		}
	}
}

