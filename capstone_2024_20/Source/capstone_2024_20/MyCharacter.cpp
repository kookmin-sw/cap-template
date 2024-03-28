#include "MyCharacter.h"

#include "MyPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


class AStaticMeshActor;
// Sets default values
AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	TextWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	TextWidget->SetupAttachment(GetMesh());
	TextWidget->SetRelativeLocation(FVector(-60.0f,0.0f,180.0f));
	TextWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/WidgetBlueprints/NewWidgetBlueprint"));
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

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));

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
		

		if(FMath::IsNearlyEqual(M_SpringArmComponent->TargetArmLength, TargetArmLength, 0.01f)
			&& M_SpringArmComponent->GetComponentRotation().Equals(TargetRotation, 0.01f))
			bIsChanging = false;
		
	}
}

//충돌 처리
void AMyCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(CurrentPlayerState != PlayerState::DRAGGING)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hit"));
		TextWidget->SetVisibility(true);
		bIsOverlap = true;
	
		for (const FString& Tag : ObjectList)
		{
			if (OtherComp->ComponentTags.Contains(Tag))
			{
				CurrentHitObjectName = Tag;
				break;
			}
		}

		CurrentHitObject = OtherActor;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, CurrentHitObject->GetName());
	}
		
}

void AMyCharacter::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(CurrentPlayerState != PlayerState::DRAGGING)
	{
		if(OtherComp->ComponentTags.Contains(TEXT("Object")))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hit Out"));
			TextWidget->SetVisibility(false);
			bIsOverlap = false;
		}
	}
}

bool AMyCharacter::GetIsOverLap()
{
	return bIsOverlap;
}

void AMyCharacter::SetTextWidgetVisible(bool b)
{
	TextWidget->SetVisibility(b);
}

bool AMyCharacter::GetTextWidgetVisible()
{
	return TextWidget->IsVisible();
}

void AMyCharacter::SetIsChanging(float length, FRotator rot, bool b)
{
	TargetArmLength = length;
	TargetRotation = rot;
	bIsChanging = b;
}

AActor* AMyCharacter::GetCurrentHitObject()
{
	return CurrentHitObject;
}


FString AMyCharacter::GetCurrentHitObjectName()
{
	return CurrentHitObjectName;
}

void AMyCharacter::SpawnCannonBall()
{
	if (!BP_CannonBallClass) return;

	// 캐릭터 앞 방향에 캐논볼을 소환할 위치 및 회전 계산
	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
	FRotator SpawnRotation = GetActorRotation();

	
	// 캐논볼 소환
	SpawnedCannonBall = GetWorld()->SpawnActor<AActor>(BP_CannonBallClass, SpawnLocation, SpawnRotation);

	if (SpawnedCannonBall != nullptr)
	{
		// 캐논볼을 캐릭터의 RootComponent에 붙입니다.
		SpawnedCannonBall->AttachToComponent(GetRootComponent(),FAttachmentTransformRules::KeepWorldTransform);
	}

}

void AMyCharacter::SetPlayerState(PlayerState NewPlayerState)
{
	CurrentPlayerState = NewPlayerState;
}

void AMyCharacter::DestroyCannonBall()
{
	if(SpawnedCannonBall)
	{
		SpawnedCannonBall->Destroy();
		SpawnedCannonBall = nullptr;
	}	
}

void AMyCharacter::DragObject()
{
	CurrentHitObject->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

	if (CurrentHitObject)
	{
		TArray<UPrimitiveComponent*> Components;
		CurrentHitObject->GetComponents<UPrimitiveComponent>(Components);

		for (UPrimitiveComponent* Component : Components)
		{
			if (!Component->GetName().Equals(TEXT("Box")))
			{
				Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}
		}
	}
                    

}

void AMyCharacter::DropObject(AActor* ship)
{
	CurrentHitObject->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CurrentHitObject->AttachToActor(ship, FAttachmentTransformRules::KeepWorldTransform);

	if (CurrentHitObject)
	{
		TArray<UPrimitiveComponent*> Components;
		CurrentHitObject->GetComponents<UPrimitiveComponent>(Components);

		for (UPrimitiveComponent* Component : Components)
		{
			Component->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
	}
}









