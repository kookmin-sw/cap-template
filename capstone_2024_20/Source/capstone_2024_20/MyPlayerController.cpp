// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "CannonControlStrategy.h"
#include "CharacterControlStrategy.h"
#include "MyShip.h"
#include "ShipControlStrategy.h"
#include "Kismet/GameplayStatics.h"

AMyPlayerController::AMyPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	static ConstructorHelpers::FObjectFinder<UInputAction> AC_Move(
		TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/Actions/Move.Move'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> AC_Interaction(
		TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/Actions/Interaction.Interaction'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> AC_Shoot(
		TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/Actions/Shoot.Shoot'"));
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_Default_Mapping(
		TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Inputs/Mappings/IMC_test.IMC_test'"));
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_Shoot_Mapping(
		TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Inputs/Mappings/IMC_Cannon.IMC_Cannon'"));

	MoveAction = AC_Move.Object;
	InteractionAction = AC_Interaction.Object;
	ShootAction = AC_Shoot.Object;
	DefaultMappingContext = IMC_Default_Mapping.Object;
	CannonMappingContext = IMC_Shoot_Mapping.Object;

	// test

	CurrentStrategy = new CharacterControlStrategy();
}


void AMyPlayerController::BeginPlay()
{
	//플레이어 할당
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(
			-1, 60.0f, FColor::Emerald, TEXT("HasAutority"));
	}

	//배 할당
	TArray<AActor*> FoundShips;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyShip::StaticClass(), FoundShips);
	if (FoundShips.Num() > 0)
	{
		Ship = Cast<APawn>(FoundShips[0]);
	}

	// 매핑 컨텐스트 할당
	Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem != nullptr)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	Player = Cast<AMyCharacter>(GetPawn());
	if (Player)
	{
		ControlledActor = Player;
		if (Player->InputComponent)
			SetupInputComponent(Player->InputComponent);

		// else
		// {
		// 	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("InputComponent NULL"));
		// }
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player NULL"));
	}
}

void AMyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!HasAuthority())
	{
		if (!Player || flag)
		{
			Player = Cast<AMyCharacter>(GetPawn());
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player NULL"));

			if (Player)
			{
				ControlledActor = Player;
				if (Player->InputComponent)
				{
					SetupInputComponent(Player->InputComponent);
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player Component NOT NULL"));
					flag = false;
				}
			}
		}
	}
}


void AMyPlayerController::SetupInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (Input != nullptr)
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);
		Input->BindAction(InteractionAction, ETriggerEvent::Started, this, &AMyPlayerController::Interaction);
		Input->BindAction(ShootAction, ETriggerEvent::Started, this, &AMyPlayerController::Shoot);
	}
}

void AMyPlayerController::Move(const FInputActionInstance& Instance)
{
	if (CurrentStrategy != nullptr)
	{
		CurrentStrategy->Move(Instance, ControlledActor,this, GetWorld()->GetDeltaSeconds());
	}
}


//상호 작용 & (스테이지 클리어)
void AMyPlayerController::Interaction(const FInputActionInstance& Instance)
{
	if (Player->GetIsOverLap())
	{
		UE_LOG(LogTemp, Log, TEXT("interaction"));
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
		TargetArmLength = 6000.0f;
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
		// 플레이어가 현재 선택/접근한 오브젝트의 이름을 비교
		if (Player->GetCurrentHitObjectName().Equals(TEXT("SteelWheel")))
		{
			// 현재 접근한 오브젝트가 "SteelWheel"이면, 컨트롤 모드를 SHIP으로 변경
			SetControlMode(ControlMode::SHIP);
			LastMappingContext = DefaultMappingContext;
			CurrentStrategy = new ShipControlStrategy();
			ControlledActor = Ship;
		}
		else if (Player->GetCurrentHitObjectName().Equals(TEXT("Cannon")))
		{
			// 현재 접근한 오브젝트가 "Cannon"이면, 컨트롤 모드를 CANNON으로 변경
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("ChangeMapping"));
			SetControlMode(ControlMode::CANNON);
			Subsystem->RemoveMappingContext(DefaultMappingContext);
			Subsystem->AddMappingContext(CannonMappingContext, 0);
			LastMappingContext = CannonMappingContext;
			CurrentStrategy = new CannonControlStrategy();
			ControlledActor = Player->GetCurrentHitObject();
			Cannon = Cast<AMyCannon>(Player->GetCurrentHitObject());
		}
		break;

	case ControlMode::SHIP:
	case ControlMode::CANNON:
		// 현재 컨트롤 모드가 SHIP 또는 CANNON일 경우, 무조건 CHARACTER 모드로 전환
		SetControlMode(ControlMode::CHARACTER);
		Subsystem->RemoveMappingContext(LastMappingContext);
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		LastMappingContext = DefaultMappingContext;
		CurrentStrategy = new CharacterControlStrategy();
		ControlledActor = Player;
		break;
	}
}

void AMyPlayerController::Shoot(const FInputActionInstance& Instance)
{
	if (IsLocalController())
	{
		ServerRPC_Shoot(Cannon);
	}
}

void AMyPlayerController::ServerRPC_Shoot_Implementation(AMyCannon* CannonActor)
{
	if (HasAuthority())
	{
		CannonActor->FireCannon();
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Shooting!"));
	}
}

void AMyPlayerController::ServerRPC_MoveCannon_Implementation(AMyCannon* CannonActor, FRotator newRot)
{
	if(HasAuthority())
	{
		CannonActor->MultiCastRPC_MoveCannon(newRot);
	}
}
