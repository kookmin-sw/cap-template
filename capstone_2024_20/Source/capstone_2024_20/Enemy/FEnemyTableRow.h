#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FEnemyTableRow.generated.h"

USTRUCT()
struct CAPSTONE_2024_20_API FEnemyTableRow : public FTableRowBase
{
	GENERATED_BODY();
	
	UPROPERTY(EditAnyWhere)
	FString Id;

	UPROPERTY(EditAnyWhere)
	FString FilePath;

	UPROPERTY(EditAnyWhere)
	int32 MaxHp;

	UPROPERTY(EditAnyWhere)
	int32 MoveSpeed;

	UPROPERTY(EditAnywhere)
	int32 SpawnPeriod;
};
