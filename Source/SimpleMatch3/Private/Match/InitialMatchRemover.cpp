#include "Match/InitialMatchRemover.h"
#include "Pieces/PieceHelpers.h"
#include "Utility/TestMacros.h"

void UInitialMatchRemover::Initialize(UBasicMatch3ToolProvider* basicMatch3ToolProvider)
{
	BasicMatch3ToolProvider = basicMatch3ToolProvider;
}

void UInitialMatchRemover::Clear()
{
	BasicMatch3ToolProvider = nullptr;
}

void UInitialMatchRemover::RemoveInitialMatches(UTileGrid* TileGrid)
{
	const auto MatchFinder = BasicMatch3ToolProvider->MatchFinder;
	const auto MatchIdentifier = BasicMatch3ToolProvider->MatchIdentifier;

	auto MatchingPieceVectors = MatchFinder->TryFindAllMatches(TileGrid);

	if (MatchingPieceVectors.size() <= 0)
	{
		return;
	}

	auto IdentifiedMatches = MatchIdentifier->IdentifyPlural(MatchingPieceVectors);

	do
	{
		for (int i = 0; i < IdentifiedMatches.size(); i++)
		{
			ChangeMidElementWithDifferentPiece(IdentifiedMatches[i].Pieces, TileGrid);
		}

		MatchingPieceVectors = MatchFinder->TryFindAllMatches(TileGrid);
		IdentifiedMatches = MatchIdentifier->IdentifyPlural(MatchingPieceVectors);
	}
	while (IdentifiedMatches.size() > 0);
}

void UInitialMatchRemover::ChangeMidElementWithDifferentPiece(TArray<APiece*>& MatchingPieces, const UTileGrid* TileGrid) const
{
	const int32 MidElementIndex = MatchingPieces.Num() / 2;
	const auto MidElement = MatchingPieces[MidElementIndex];
	const auto MidElementTile = TileGrid->GetTile(MidElement->ParentI, MidElement->ParentJ);
	const auto MidElementType = MidElement->Settings.Type;

	bool IsDestroyed = MidElementTile->DetachPiece()->Destroy();
	auto DifferentPieceType = PieceHelpers::GetRandomPieceType(MidElementType);

	const auto NewPiece = BasicMatch3ToolProvider->PieceGenerator->Generate(DifferentPieceType, MidElementTile->GetActorLocation(), FRotator::ZeroRotator);
	MidElementTile->AttachPiece(NewPiece, true);
}
