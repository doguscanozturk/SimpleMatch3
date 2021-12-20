#include "Pieces/PieceGenerator.h"
#include "Pieces/PieceHelpers.h"
#include "ThirdParty/boolinq.h"
#include "Utility/TestMacros.h"

void UPieceGenerator::Initialize(const TSubclassOf<AActor> pieceBP, UPieceVariations* pieceVariations)
{
	PieceBP = pieceBP;
	PieceVariations = pieceVariations;
}

void UPieceGenerator::Clear()
{
	PieceBP = nullptr;
	PieceVariations = nullptr;
}

APiece* UPieceGenerator::GenerateRandom(const FVector Position, const FRotator Rotation) const
{
	const auto RandomType = PieceHelpers::GetRandomPieceType();
	return Generate(RandomType, Position, Rotation);
}

APiece* UPieceGenerator::Generate(const EPieceType Type, const FVector Position, const FRotator Rotation) const
{
	const auto Piece = GetWorld()->SpawnActor<APiece>(PieceBP, Position, Rotation);
	const auto PieceData = GetPieceData(Type);
	Piece->Set(PieceData);
	return Piece;
}

FPieceData UPieceGenerator::GetPieceData(const EPieceType Type) const
{
	for (const auto Variation : PieceVariations->Variations)
	{
		if (Variation.Type == Type)
		{
			return Variation;
		}
	}

	throw std::exception("Don't have PieceData for that type!");
}
