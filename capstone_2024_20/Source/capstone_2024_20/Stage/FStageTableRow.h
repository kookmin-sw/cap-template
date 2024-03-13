#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FStageTableRow.generated.h"

USTRUCT()
struct CAPSTONE_2024_20_API FStageTableRow : public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(EditAnyWhere)
	FString Id;

	UPROPERTY(EditAnyWhere)
	FString MapId;

	UPROPERTY(EditAnyWhere)
	FString ShipId;

	UPROPERTY(EditAnyWhere)
	FString EnemyId;
	
	UPROPERTY(EditAnyWhere)
	FString EventId;

	UPROPERTY(EditAnyWhere)
	FString TriggerIdClear;

	UPROPERTY(EditAnyWhere)
	FString TriggerIdGameOver;
};
