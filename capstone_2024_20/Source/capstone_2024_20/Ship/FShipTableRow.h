#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FShipTableRow.generated.h"

USTRUCT()
struct CAPSTONE_2024_20_API FShipTableRow : public FTableRowBase
{
	GENERATED_BODY();
	
	UPROPERTY(EditAnyWhere)
	FString Id;

	UPROPERTY(EditAnyWhere)
	FString FilePath;

	UPROPERTY(EditAnywhere)
	int32 SteerSpeed;
};
