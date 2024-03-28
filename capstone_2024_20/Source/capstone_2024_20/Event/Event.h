#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Event.generated.h"

UCLASS()
class CAPSTONE_2024_20_API AEvent : public AActor
{
	GENERATED_BODY()

public:
	AEvent();

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
};
