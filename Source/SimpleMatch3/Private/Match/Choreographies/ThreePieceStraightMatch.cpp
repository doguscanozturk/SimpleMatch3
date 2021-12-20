#include "Match/Choreographies/ThreePieceStraightMatch.h"
#include "Utility/MatrixHelpers.h"

int UThreePieceStraightMatch::GetMinPieceRequirement()
{
	return 3;
}

void UThreePieceStraightMatch::Initialize()
{
	const auto Choreography = GetChoreography();
	const auto SecondVersion = MatrixHelpers::RotateMatrixAnticlockwise(Choreography);

	InitializeChoreography(Choreography);
	InitializeChoreography(SecondVersion);
}

FMatchMatrix UThreePieceStraightMatch::GetChoreography()
{
	FMatchMatrix DefaultMatrix({
		FMatchMatrixRow(TArray<uint8>{1}),
		FMatchMatrixRow(TArray<uint8>{1}),
		FMatchMatrixRow(TArray<uint8>{1})
	});

	return DefaultMatrix;
}
