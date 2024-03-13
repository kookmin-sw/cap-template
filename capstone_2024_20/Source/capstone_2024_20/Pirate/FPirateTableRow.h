#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FPirateTableRow.generated.h"

USTRUCT()
struct CAPSTONE_2024_20_API FPirateTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Id;
	
	UPROPERTY(EditAnywhere)
	FString FilePath;
	
	UPROPERTY(EditAnywhere)
	int MoveSpeed;
	
	UPROPERTY(EditAnywhere)
	int AttackDamage;
};
