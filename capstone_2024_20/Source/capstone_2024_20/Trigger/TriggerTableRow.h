#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TriggerTableRow.generated.h"

USTRUCT()
struct CAPSTONE_2024_20_API FTriggerTableRow : public FTableRowBase
{
	GENERATED_BODY();
	
	UPROPERTY(EditAnyWhere)
	FString Id;
};
