#include "MyCharacter.h"

#include "MyPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// for (TActorIterator<APawn> It(GetWorld()); It; ++It)
	// {
	// 	APawn* FoundPawn = *It;
	// 	if (FoundPawn != nullptr && FoundPawn->GetName() == "MyShip")
	// 	{
	// 		Ship = FoundPawn;
	// 		break;
	// 	}
	// }
	
	// TArray<AActor*> arrOutActors;
	// UGameplayStatics::GetAllActorsOfClass(GetWorld(),AMyShip::StaticClass(),arrOutActors);
	// Ship = Cast<APawn>(arrOutActors[0]);
	
	TextWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	TextWidget->SetupAttachment(GetMesh());
	TextWidget->SetRelativeLocation(FVector(-60.0f,0.0f,180.0f));
	TextWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/UMG/NewWidgetBlueprint"));
	if(UI_HUD.Succeeded())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("UMG Success"));
		TextWidget->SetWidgetClass(UI_HUD.Class);
		TextWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
		TextWidget->SetVisibility(false);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("UMG Failed"));
	}
	
	M_SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	M_CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	M_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = GetCapsuleComponent();

	GetMesh()->AttachToComponent(GetCapsuleComponent(),FAttachmentTransformRules::KeepRelativeTransform);
	M_SpringArmComponent->SetupAttachment(GetCapsuleComponent());
	M_CameraComponent->SetupAttachment(M_SpringArmComponent);
	M_MeshComponent->SetupAttachment(GetCapsuleComponent());

	GetCapsuleComponent()->SetCapsuleHalfHeight(88.0f);
	GetCapsuleComponent()->SetCapsuleRadius(20.0f);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f,0.0f,-88.0f), FRotator(0.0f, -90.0f, 0.0f));

	M_SpringArmComponent->TargetArmLength = 1000.0f;
	M_SpringArmComponent->SetRelativeLocationAndRotation(FVector(0.0f,0.0f,40.0f), FRotator(-25.0f,0.0f,0.0f));
	//M_SpringArmComponent->bDoCollisionTest = false;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));
	if(StaticMesh.Object)
	{
		M_MeshComponent->SetStaticMesh(StaticMesh.Object);
		M_MeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> AC_Move(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/Actions/Move.Move'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> AC_Interaction(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/Actions/Interaction.Interaction'"));
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_Mapping(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Inputs/Mappings/IMC_test.IMC_test'"));
	
	MoveAction = AC_Move.Object;
	InteractionAction = AC_Interaction.Object;
	DefaultMappingContext = IMC_Mapping.Object;
	
	
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));

	// 플레이어 컨트롤러에 입력 매핑 집어넣기
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(Controller);

	if(PlayerController != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if(Subsystem != nullptr)
		{
			Subsystem->AddMappingContext(DefaultMappingContext,0);
		}
	}

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&AMyCharacter::BeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMyCharacter::EndOverlap);
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// debug
	if(bIsChanging)
	{
		M_SpringArmComponent->TargetArmLength = FMath::FInterpTo(M_SpringArmComponent->TargetArmLength, TargetArmLength, DeltaTime, ChangeSpeed);

		FRotator CurrentRotation = M_SpringArmComponent->GetRelativeRotation();
		FRotator newRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, ChangeSpeed);
		M_SpringArmComponent->SetRelativeRotation(newRotation);
		

		if(FMath::IsNearlyEqual(M_SpringArmComponent->TargetArmLength, TargetArmLength, 0.01f
			&& M_SpringArmComponent->GetComponentRotation().Equals(TargetRotation, 0.01f)))
			bIsChanging = false;
		
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if(Input != nullptr)
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
		Input->BindAction(InteractionAction, ETriggerEvent::Started, this, &AMyCharacter::Interaction);
	}
}

void AMyCharacter::Move(const FInputActionInstance& Instance)
{
	FVector2D MoveVec = Instance.GetValue().Get<FVector2D>();

	if(Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
     	const FRotator YawRotation(0,Rotation.Yaw,0);
     	const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
     	const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		if(CurrentControlMode == ControlMode::CHARACTER)
		{
			AddMovementInput(ForwardDir, MoveVec.Y);
			AddMovementInput(RightDir, MoveVec.X);
		}
		else if(CurrentControlMode == ControlMode::SHIP)
		{
			// Ship->SetActorLocation(Ship->GetActorLocation() + FVector(MoveVec.Y, MoveVec.X, 0.0f) * 3.0f);
			//
			// FVector DesiredDirection = ForwardDir * MoveVec.X + RightDir * MoveVec.Y;
			// DesiredDirection.Z = 0.0f;
			//
			// FRotator DesiredRotation = DesiredDirection.Rotation();
			// FRotator NewShipRotation(0.0f, -DesiredRotation.Yaw + 90.0f, 0.0f );
			//
			// float InterpSpeed = 0.2f;
			//
			// FRotator CurrentRotation = Ship->GetActorRotation();
			// FRotator SmoothedRotation = FMath::RInterpTo(CurrentRotation, NewShipRotation, GetWorld()->GetDeltaSeconds(), InterpSpeed);
			//
			// // 회전 적용
			// Ship->SetActorRotation(SmoothedRotation);


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
}

//상호 작용 & (스테이지 클리어)
void AMyCharacter::Interaction(const FInputActionInstance& Instance)
{
	if(bIsOverlap)
	{
		UE_LOG(LogTemp,Log,TEXT("interaction"));
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Interaction"));
		TextWidget->SetVisibility(!TextWidget->IsVisible());
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

void AMyCharacter::SetControlMode(ControlMode NewControlMode)
{
	CurrentControlMode = NewControlMode;

	switch (CurrentControlMode)
	{
	case ControlMode::SHIP:
		bUseControllerRotationYaw = false;
		TargetArmLength = 3000.0f;
		TargetRotation = FRotator(-70.0f, 0.0f, 0.0f);
		bIsChanging = true;
		// M_SpringArmComponent->TargetArmLength = 1200.0f;
		// M_SpringArmComponent->SetRelativeRotation(FRotator(-55.0f,0.0f,0.0f));
		break;

	case ControlMode::CHARACTER:
		TargetArmLength = 1000.0f;
    	TargetRotation = FRotator(-25.0f, 0.0f, 0.0f);
		bIsChanging = true;
		// M_SpringArmComponent->TargetArmLength = 600.0f;
		// M_SpringArmComponent->SetRelativeRotation(FRotator(-25.0f,0.0f,0.0f));
		break;

	case ControlMode::CANNON:
		TargetArmLength = 1500.0f;
		TargetRotation = FRotator(-30.0f, 0.0f, 0.0f);
		bIsChanging = true;
	}
}

//모드 변환
void AMyCharacter::ViewChange()
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

//충돌 처리
void AMyCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hit"));
	TextWidget->SetVisibility(true);
	bIsOverlap = true;
}

void AMyCharacter::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hit Out"));
	TextWidget->SetVisibility(false);
	bIsOverlap = false;
}




