#pragma once

#include "CoreMinimal.h"
#include "RoomData.generated.h"

namespace RoomTEXT
{
	const static FName NAME = TEXT("RoomName");
	const static FName CODE = TEXT("RoomCode");
}

USTRUCT(BlueprintType)
struct FRoomData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Code;
};
