#pragma once
#include "MatchMatrixRow.generated.h"

USTRUCT()
struct FMatchMatrixRow
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	TArray<uint8> Elements;
 
	FMatchMatrixRow()
	{
		Elements.Empty();
	}

	explicit FMatchMatrixRow(const uint8 ColumnCount)
	{
		Elements.Init(0, ColumnCount);
	}

	explicit FMatchMatrixRow(const TArray<uint8> PreInitializedArray)
	{
		Elements = PreInitializedArray;
	}
};
