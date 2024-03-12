// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "MyShip.h"
#include "Kismet/GameplayStatics.h"

AMyPlayerController::AMyPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UInputAction> AC_Move(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/Actions/Move.Move'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> AC_Interaction(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/Actions/Interaction.Interaction'"));
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_Mapping(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Inputs/Mappings/IMC_test.IMC_test'"));
	
	MoveAction = AC_Move.Object;
	InteractionAction = AC_Interaction.Object;
	DefaultMappingContext = IMC_Mapping.Object;

	// test 

	
}


void AMyPlayerController::BeginPlay()
{
	Player = Cast<AMyCharacter>(GetCharacter());
	TArray<AActor*> FoundShips;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyShip::StaticClass(), FoundShips);

	if (FoundShips.Num() > 0)
	{
		Ship = Cast<APawn>(FoundShips[0]);
	}

	if(Ship != nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("shipship"));
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem != nullptr)
	{
		Subsystem->AddMappingContext(DefaultMappingContext,0);
	}
	SetupPlayerInputComponent(Player->InputComponent);

}

void AMyPlayerController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("afdsafdsfdas"));
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if(Input != nullptr)
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);
		Input->BindAction(InteractionAction, ETriggerEvent::Started, this, &AMyPlayerController::Interaction);
	}
}

void AMyPlayerController::Move(const FInputActionInstance& Instance)
{
	FVector2D MoveVec = Instance.GetValue().Get<FVector2D>();

		const FRotator Rotation = this->GetControlRotation();
     	const FRotator YawRotation(0,Rotation.Yaw,0);
     	const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
     	const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		if(CurrentControlMode == ControlMode::CHARACTER)
		{
			Player->AddMovementInput(ForwardDir, MoveVec.Y);
			Player->AddMovementInput(RightDir, MoveVec.X);
		}
		else if(CurrentControlMode == ControlMode::SHIP)
		{
			float MoveSpeed = 600.0f; // 선박의 전진 속도
			float RotationSpeed = 10.0f; // 회전 속도 (도/초)
			float DeltaTime = GetWorld()->GetDeltaSeconds();

			// 전진 처리: 앞 방향키 입력에 따라
			if(MoveVec.Y > 0)
			{
				FVector ForwardDirection = Ship->GetActorForwardVector();
				Ship->AddActorWorldOffset(-ForwardDirection * MoveVec.Y * MoveSpeed * DeltaTime, true);
			

				// 회전 처리: 좌우 방향키 입력에 따라
				if(MoveVec.X != 0)
				{
					FRotator CurrentRotation = Ship->GetActorRotation();
					// 목표 회전 각도를 계산합니다 (현재 Yaw 값 + 입력에 따른 변화량).
					float TargetYaw = CurrentRotation.Yaw + MoveVec.X * RotationSpeed * DeltaTime;
					// 회전 각도를 -30도에서 30도 사이로 제한합니다.
					TargetYaw = FMath::Clamp(TargetYaw, -360.0f, 360.0f);

					// 실제 회전 적용
					Ship->SetActorRotation(FRotator(0.0f, TargetYaw, 0.0f));
				}
			}
		}
}


//상호 작용 & (스테이지 클리어)
void AMyPlayerController::Interaction(const FInputActionInstance& Instance)
{
	if(Player->GetIsOverLap())
	{
		UE_LOG(LogTemp,Log,TEXT("interaction"));
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Interaction"));
		Player->SetTextWidgetVisible(!Player->GetTextWidgetVisible());
		ViewChange();

		//스테이지 클리어 팝업 띄우기
		// UUserWidget* PopUpWidget = CreateWidget<UUserWidget>(GetWorld(), ClearPopUpWidgetClass);
		// if(PopUpWidget != nullptr)
		// {
		// 	PopUpWidget->AddToViewport();
		// 	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(Controller);
		// 	PlayerController->bShowMouseCursor = true;
		// 	FInputModeUIOnly InputMode;
		// 	PlayerController->SetInputMode(InputMode);
		// }
	}
}

void AMyPlayerController::SetControlMode(ControlMode NewControlMode)
{
	CurrentControlMode = NewControlMode;

	switch (CurrentControlMode)
	{
	case ControlMode::SHIP:
		Player->bUseControllerRotationYaw = false;
		TargetArmLength = 3000.0f;
		TargetRotation = FRotator(-70.0f, 0.0f, 0.0f);
		Player->SetIsChanging(TargetArmLength, TargetRotation, true);
		break;

	case ControlMode::CHARACTER:
		TargetArmLength = 1000.0f;
		TargetRotation = FRotator(-25.0f, 0.0f, 0.0f);
		Player->SetIsChanging(TargetArmLength, TargetRotation, true);
		break;

	case ControlMode::CANNON:
		TargetArmLength = 1500.0f;
		TargetRotation = FRotator(-30.0f, 0.0f, 0.0f);
		Player->SetIsChanging(TargetArmLength, TargetRotation, true);
	}
}

//모드 변환
void AMyPlayerController::ViewChange()
{
	switch (CurrentControlMode)
	{
	case ControlMode::CHARACTER:
		SetControlMode(ControlMode::SHIP);
		break;
	case ControlMode::SHIP:
		SetControlMode(ControlMode::CHARACTER);
		break;
	}
}