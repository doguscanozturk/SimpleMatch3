#include "Match/Choreographies/FivePieceTMatch.h"
#include "Utility/MatrixHelpers.h"

void UFivePieceTMatch::Initialize()
{
	const auto Choreography = GetChoreography();
	const auto SecondVersion = MatrixHelpers::RotateMatrixAnticlockwise(Choreography);
	auto ThirdVersion = MatrixHelpers::RotateMatrixAnticlockwise(SecondVersion);
	ThirdVersion.SetStartIndexOffset(FIntPoint(0, -1));
	auto FourthVersion = MatrixHelpers::RotateMatrixAnticlockwise(ThirdVersion);
	FourthVersion.SetStartIndexOffset(FIntPoint(0, -2));
	
	InitializeChoreography(Choreography);
	InitializeChoreography(SecondVersion);
	InitializeChoreography(ThirdVersion);
	InitializeChoreography(FourthVersion);
}

int UFivePieceTMatch::GetMinPieceRequirement()
{
	return 5;
}

FMatchMatrix UFivePieceTMatch::GetChoreography()
{
	FMatchMatrix Shape({
		FMatchMatrixRow({1, 1, 1}),
		FMatchMatrixRow({0, 1, 0}),
		FMatchMatrixRow({0, 1, 0})
	});

	return Shape;
}
