#include "Grid/TileGrid.h"

void UTileGrid::Initialize(const int width, const int height)
{
	Width = width;
	Height = height;

	const auto Size = Width * Height;
	Tiles.Reserve(Size);
}

void UTileGrid::Clear()
{
	for (const auto Tile : Tiles)
	{
		Tile->Clear();
		Tile->Destroy();
	}

	Tiles.Empty();
	Width = 0;
	Height = 0;
}

void UTileGrid::Insert(const int Index, ATile* Tile)
{
	Tiles.Insert(Tile, Index);
}

ATile* UTileGrid::GetTile(const int32 I, const int32 J) const
{
	if (I < 0 || J < 0 || I >= Width || J >= Height)
	{
		return nullptr;
	}

	const auto Index = (I * Height) + J;
	const auto Tile = Tiles[Index];
	return Tile;
}

ATile* UTileGrid::GetNeighborTile(const ATile* Tile, ESwipeDirection NeighborDirection) const
{
	FIntPoint NeighborIndex;

	if (Tile == nullptr)
	{
		return nullptr;
	}

	switch (NeighborDirection)
	{
	case ESwipeDirection::Left:
		if (Tile->J - 1 < 0)
		{
			return nullptr;
		}
		NeighborIndex = FIntPoint(Tile->I, Tile->J - 1);
		break;
	case ESwipeDirection::Right:
		if (Tile->J + 1 >= Height)
		{
			return nullptr;
		}
		NeighborIndex = FIntPoint(Tile->I, Tile->J + 1);
		break;
	case ESwipeDirection::Up:
		if (Tile->I - 1 < 0)
		{
			return nullptr;
		}
		NeighborIndex = FIntPoint(Tile->I - 1, Tile->J);
		break;
	case ESwipeDirection::Down:
		if (Tile->I + 1 >= Width)
		{
			return nullptr;
		}
		NeighborIndex = FIntPoint(Tile->I + 1, Tile->J);
		break;
	}
	
	const auto NeighborTile = GetTile(NeighborIndex.X, NeighborIndex.Y);
	// UE_LOG(LogTemp, Warning, TEXT("GetNeighborTile Self %s"), *Tile->GetName());
	// UE_LOG(LogTemp, Warning, TEXT("GetNeighborTile Neighbor %s"), *NeighborTile->GetName());
	return NeighborTile;
}
