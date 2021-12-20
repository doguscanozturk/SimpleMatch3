#include "Match/Choreographies/FourPieceSquareMatch.h"

int UFourPieceSquareMatch::GetMinPieceRequirement()
{
	return 4;
}

void UFourPieceSquareMatch::Initialize()
{
	InitializeChoreography(GetChoreography());
}

FMatchMatrix UFourPieceSquareMatch::GetChoreography()
{
	FMatchMatrix DefaultMatrix({
		FMatchMatrixRow(TArray<uint8>{1, 1}),
		FMatchMatrixRow(TArray<uint8>{1, 1}),
	});

	return DefaultMatrix;
}
