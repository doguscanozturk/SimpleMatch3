#include "Match/Choreographies/FivePieceLMatch.h"
#include "Utility/MatrixHelpers.h"

int UFivePieceLMatch::GetMinPieceRequirement()
{
	return 5;
}

void UFivePieceLMatch::Initialize()
{
	const auto Choreography = GetChoreography();
	const auto SecondVersion = MatrixHelpers::RotateMatrixAnticlockwise(Choreography);
	const auto ThirdVersion = MatrixHelpers::RotateMatrixAnticlockwise(SecondVersion);
	const auto FourthVersion = MatrixHelpers::RotateMatrixAnticlockwise(ThirdVersion);

	InitializeChoreography(Choreography);
	InitializeChoreography(SecondVersion);
	InitializeChoreography(ThirdVersion);
	InitializeChoreography(FourthVersion);
}

FMatchMatrix UFivePieceLMatch::GetChoreography()
{
	FMatchMatrix DefaultMatrix({
		FMatchMatrixRow({1, 0, 0}),
		FMatchMatrixRow({1, 0, 0}),
		FMatchMatrixRow({1, 1, 1})
	});

	return DefaultMatrix;
}
