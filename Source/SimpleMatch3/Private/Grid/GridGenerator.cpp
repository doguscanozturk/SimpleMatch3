#include "Grid/GridGenerator.h"
#include "Grid/TileGrid.h"

void UGridGenerator::Initialize(UPieceGenerator* pieceGenerator, UBlueprintReferences* blueprintReferences)
{
	PieceGenerator = pieceGenerator;
	BlueprintReferences = blueprintReferences;
}

void UGridGenerator::Clear()
{
	PieceGenerator = nullptr;
	BlueprintReferences = nullptr;
}

UTileGrid* UGridGenerator::Generate(FIntPoint Size)
{
	constexpr float SideLength = 600;
	const FVector StartPosition = FVector::ZeroVector;
	const FRotator StartRotation = FRotator::ZeroRotator;

	UTileGrid* TileGrid = NewObject<UTileGrid>();
	TileGrid->Initialize(Size.X, Size.Y);

	for (int i = 0; i < Size.X; i++)
	{
		for (int j = 0; j < Size.Y; j++)
		{
			auto HorizontalOffset = FVector::BackwardVector * SideLength * j;
			auto VerticalOffset = FVector::DownVector * SideLength * i;
			const auto Position = StartPosition + HorizontalOffset + VerticalOffset;
			const auto NewTile = SpawnGridTile(Position, StartRotation, i, j);
			const auto Piece = PieceGenerator->GenerateRandom(FVector::ZeroVector, FRotator::ZeroRotator);
			NewTile->AttachPiece(Piece, true);

			const auto Index = (i * Size.Y) + j;
			TileGrid->Insert(Index, NewTile);
		}
	}

	return TileGrid;
}

ATile* UGridGenerator::SpawnGridTile(FVector Position, FRotator Rotation, int I, int J)
{
	const auto GridTileBP = BlueprintReferences->GridTileBP;

	FString testName2 = FString::Printf(TEXT("GridTile - [%d,%d]"), I, J);

	ATile* Tile = GetWorld()->SpawnActor<ATile>(GridTileBP, Position, Rotation);
	Tile->SetActorLabel(testName2);
	Tile->SetFolderPath("/GridTiles");
	Tile->I = I;
	Tile->J = J;
	return Tile;
}
