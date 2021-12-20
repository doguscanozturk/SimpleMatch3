#include "Match/Choreographies/FourPieceStraightMatch.h"
#include "Utility/MatrixHelpers.h"

int UFourPieceStraightMatch::GetMinPieceRequirement()
{
	return 4;
}

void UFourPieceStraightMatch::Initialize()
{
	const auto Choreography = GetChoreography();
	const auto SecondVersion = MatrixHelpers::RotateMatrixAnticlockwise(Choreography);

	InitializeChoreography(Choreography);
	InitializeChoreography(SecondVersion);
}

FMatchMatrix UFourPieceStraightMatch::GetChoreography()
{
	FMatchMatrix DefaultMatrix({
		FMatchMatrixRow(TArray<uint8>{1}),
		FMatchMatrixRow(TArray<uint8>{1}),
		FMatchMatrixRow(TArray<uint8>{1}),
		FMatchMatrixRow(TArray<uint8>{1})
	});

	return DefaultMatrix;
}
