#pragma once

#include "CoreMinimal.h"
#include "RoomData.generated.h"

USTRUCT(BlueprintType)
struct FRoomData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Code;

	const static FName NAME_TEXT = TEXT("RoomName");
	const static FName CODE_TEXT = TEXT("RoomCode");
};
