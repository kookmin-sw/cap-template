// Fill out your copyright notice in the Description page of Project Settings.


#include "CannonBall.h"

// Sets default values
ACannonBall::ACannonBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	 ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	 RootComponent = ProjectileMesh;

	// 발사체의 물리적 충돌과 동작을 처리할 프로젝타일 무브먼트 컴포넌트를 생성합니다.
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->SetUpdatedComponent(ProjectileMesh);
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 6000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// 충돌 시 OnHit 함수를 호출하도록 설정합니다.
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ACannonBall::OnHit);
}

// Called when the game starts or when spawned
void ACannonBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACannonBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ACannonBall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 여기에 충돌 시 필요한 로직을 구현합니다. 예를 들면, 폭발 이펙트 생성, 피해 적용 등이 있습니다.
	// 이 예제에서는 단순히 로그를 출력하는 것으로 처리합니다.
	UE_LOG(LogTemp, Warning, TEXT("Projectile hit: %s"), *OtherActor->GetName());

	// 충돌 후 발사체를 제거합니다.
	Destroy();
}
