// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "CannonControlStrategy.h"
#include "CharacterControlStrategy.h"
#include "MyShip.h"
#include "ShipControlStrategy.h"
#include "Kismet/GameplayStatics.h"

class AStaticMeshActor;

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
	static ConstructorHelpers::FObjectFinder<UInputAction> AC_DraggingRotate(
		TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/Actions/DraggingRotate.DraggingRotate'"));
	
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_Default_Mapping(
		TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Inputs/Mappings/IMC_test.IMC_test'"));
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_Shoot_Mapping(
		TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Inputs/Mappings/IMC_Cannon.IMC_Cannon'"));

	MoveAction = AC_Move.Object;
	InteractionAction = AC_Interaction.Object;
	ShootAction = AC_Shoot.Object;
	DraggingRotateAction = AC_DraggingRotate.Object;
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
		Ship = Cast<AMyShip>(FoundShips[0]);
		
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
			SetupPlayerInputComponent(Player->InputComponent);
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
					SetupPlayerInputComponent(Player->InputComponent);
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player Component NOT NULL"));
					flag = false;
				}
			}
		}
	}

	// 키를 누르고 있으면 시간을 측정
	if (bIsPressingKey)
	{
		PressDuration += GetWorld()->DeltaTimeSeconds;
	}
	
}


void AMyPlayerController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (Input != nullptr)
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);
		Input->BindAction(InteractionAction, ETriggerEvent::Started, this, &AMyPlayerController::Interaction_Pressed);
		Input->BindAction(InteractionAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Interaction_Trigger);
		Input->BindAction(InteractionAction, ETriggerEvent::Completed, this, &AMyPlayerController::Interaction_Released);
		Input->BindAction(DraggingRotateAction, ETriggerEvent::Triggered, this, &AMyPlayerController::DraggingRotate);
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
	}
}

void AMyPlayerController::Interaction_Pressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Interaction start"));
	bIsPressingKey = true;
	PressDuration = 0.0f; // 타이머 리셋
}

void AMyPlayerController::Interaction_Trigger()
{
	if (Player->GetIsOverLap())
	{
		// 여기서 PressDuration을 사용하여 길게 누르고 있는지 판단하고, 원하는 로직 실행
		if (PressDuration >= 3.0f) // 3초 넘게 누르면 DRAGGING 상태로 전환
		{
			//무언가를 끌고 있지 않을때만 끌기가 가능하게
			if(Player->CurrentPlayerState == AMyCharacter::PlayerState::NONE)
				Player->DragObject();

			Player->SetPlayerState(AMyCharacter::PlayerState::DRAGGING);
			
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("ing"));
		}
	}
}


void AMyPlayerController::Interaction_Released()
{
	bIsPressingKey = false;
	if (Player->GetIsOverLap())
	{
		if (PressDuration < 3.0f) // 3초 안됐으면 그냥 상호작용
		{
			UE_LOG(LogTemp, Log, TEXT("interaction"));
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Interaction"));
			Player->SetTextWidgetVisible(!Player->GetTextWidgetVisible());
			ViewChange();
		}
	
		else
		{
			Player->SetPlayerState(AMyCharacter::PlayerState::NONE);
			//이동하는 오브젝트 놔주는 함수
			//다시 Ship의 자식으로
			Player->DropObject(Ship);
			
		}
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Interaction end"));
	}
}

void AMyPlayerController::DraggingRotate(const FInputActionInstance& Instance)
{
	if(Player->CurrentPlayerState==AMyCharacter::PlayerState::DRAGGING)
	{
		FRotator NewRotation = FRotator(0.0f, Instance.GetValue().Get<float>(),0.0f);
		Player->GetCurrentHitObject()->AddActorLocalRotation(NewRotation);
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
		TargetRotation = Cannon->GetActorRotation() + FRotator(-30.0f, -90.0f, 0.0f);
		//TargetRotation = FRotator(-30.0f, 0.0f, 0.0f);
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
			
			LastMappingContext = DefaultMappingContext;
			CurrentStrategy = new ShipControlStrategy;
			ControlledActor = Ship;
			SetControlMode(ControlMode::SHIP);
		}
		else if (Player->GetCurrentHitObjectName().Equals(TEXT("Cannon")))
		{

			// if 캐릭터 스테이트가 carrying이라면
			if(Player->CurrentPlayerState == AMyCharacter::PlayerState::NONE)
			{
				// else None 이라면 아니면 (아무것도 들고 있지 않은 상태면 Cannon 조작으로
				// 현재 접근한 오브젝트가 "Cannon"이면, 컨트롤 모드를 CANNON으로 변경
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("ChangeMapping"));
				Subsystem->RemoveMappingContext(DefaultMappingContext);
				Subsystem->AddMappingContext(CannonMappingContext, 0);
				LastMappingContext = CannonMappingContext;
				CurrentStrategy = new CannonControlStrategy();
				ControlledActor = Player->GetCurrentHitObject();
				Cannon = Cast<AMyCannon>(Player->GetCurrentHitObject());
				SetControlMode(ControlMode::CANNON);
			}
			else if(Player->CurrentPlayerState == AMyCharacter::PlayerState::CARRYING)
			{
				//나중에 옮기는 오브젝트가 뭔지도 검사
				//지금은 무조건 대포알로 간주

				//대포 장전
				Cannon = Cast<AMyCannon>(Player->GetCurrentHitObject());
				Cannon->SetIsLoad(true);
				Player->SetPlayerState(AMyCharacter::PlayerState::NONE);
				Player->DestroyCannonBall();
			}

			
		}
		else if (Player->GetCurrentHitObjectName().Equals(TEXT("CannonBallBox")))
		{
			if(Player->CurrentPlayerState == AMyCharacter::PlayerState::NONE)
			{
				// 현재 접근한 오브젝트가 "CannonBallBox"면 캐논볼 생성
				Player->SpawnCannonBall();
				Player->SetPlayerState(AMyCharacter::PlayerState::CARRYING);
			}
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
	//대포알이 장전됐을때만 발사 가능
	if (IsLocalController() && Cannon->GetIsLoad())
	{
		ServerRPC_Shoot(Cannon);
		Cannon->SetIsLoad(false);
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

void AMyPlayerController::ServerRPC_RotateCannon_Implementation(AMyCannon* CannonActor, FRotator newRot)
{
	if(HasAuthority())
	{
		CannonActor->MultiCastRPC_RotateCannon(newRot);
	}
}

void AMyPlayerController::ServerRPC_MoveShip_Loc_Implementation(FVector newLoc)
{
	if(HasAuthority())
	{
		Ship->MulticastRPC_SetShipLocation(newLoc);
	}
}

void AMyPlayerController::ServerRPC_MoveShip_Rot_Implementation(float newYaw, float speed)
{
	if(HasAuthority())
	{
		FRotator newRot = FRotator(0.0f, newYaw*speed*GetWorld()->GetDeltaSeconds(), 0.0f) + Ship->GetActorRotation();
		Ship->TargetRotation = newRot;
		//Ship->MulticastRPC_SetShipRotation(newYaw, speed);
	}
}


