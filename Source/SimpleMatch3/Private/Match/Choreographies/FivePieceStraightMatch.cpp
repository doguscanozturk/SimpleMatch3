#include "Match/Choreographies/FivePieceStraightMatch.h"
#include "Utility/MatrixHelpers.h"

int UFivePieceStraightMatch::GetMinPieceRequirement()
{
	return 5;
}

void UFivePieceStraightMatch::Initialize()
{
	const auto Choreography = GetChoreography();
	const auto SecondVersion = MatrixHelpers::RotateMatrixAnticlockwise(Choreography);

	InitializeChoreography(Choreography);
	InitializeChoreography(SecondVersion);
}

FMatchMatrix UFivePieceStraightMatch::GetChoreography()
{
	FMatchMatrix DefaultMatrix({FMatchMatrixRow({1, 1, 1, 1, 1})});

	return DefaultMatrix;
}
