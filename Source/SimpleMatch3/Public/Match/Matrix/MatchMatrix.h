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
		StartIndexOffset = FIntPoint::ZeroValue;
	}

	FMatchMatrix(const size_t rowCount, const size_t columnCount)
	{
		Rows.Init(FMatchMatrixRow(columnCount), rowCount);
		StartIndexOffset = FIntPoint::ZeroValue;
	}

	FMatchMatrix(TArray<FMatchMatrixRow> rows)
	{
		Rows = rows;
		StartIndexOffset = FIntPoint::ZeroValue;
	}

	int8 GetElementValue(const int8 I, const int8 J)
	{
		return Rows[I].Elements[J];
	}

	void SetStartIndexOffset(FIntPoint Offset)
	{
		StartIndexOffset = Offset;
	}

	FIntPoint GetStartIndexOffset()
	{
		return StartIndexOffset;
	}

private:
	FIntPoint StartIndexOffset;
};
