#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FMapTableRow.generated.h"

USTRUCT()
struct CAPSTONE_2024_20_API FMapTableRow : public FTableRowBase
{
	GENERATED_BODY();
	
	UPROPERTY(EditAnyWhere)
	FString Id;

	UPROPERTY(EditAnyWhere)
	FString FilePath;
};
