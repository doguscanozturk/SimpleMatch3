#pragma once
#include "MatchMatrixRow.h"
#include "MatchMatrix.generated.h"

USTRUCT()
struct FMatchMatrix
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	TArray<FMatchMatrixRow> Rows;

	FMatchMatrix()
	{
		Rows.Empty();
	}

	FMatchMatrix(const size_t rowCount, const size_t columnCount)
	{
		Rows.Init(FMatchMatrixRow(columnCount), rowCount);
	}

	FMatchMatrix(TArray<FMatchMatrixRow> rows)
	{
		Rows = rows;
	}
	
	int8 GetElementValue(const int8 I, const int8 J)
	{
		return Rows[I].Elements[J];
	}
};
