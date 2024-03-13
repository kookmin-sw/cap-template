#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FEventTableRow.generated.h"

USTRUCT()
struct CAPSTONE_2024_20_API FEventTableRow : public FTableRowBase
{
	GENERATED_BODY();
	
	UPROPERTY(EditAnyWhere)
	FString Id;

	UPROPERTY(EditAnywhere)
	int32 SpawnPeriod;
};
