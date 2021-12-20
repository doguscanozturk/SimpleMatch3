#pragma once
#include "Tile.h"
#include "Controllers/SwipeDirection.h"
#include "TileGrid.generated.h"

UCLASS()
class UTileGrid : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int32 Height;
	
	UPROPERTY(BlueprintReadOnly)
	int32 Width;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<ATile*> Tiles;
	
	void Initialize(int32 width, int32 height);
	
	void Clear();

	void Insert(int32 Index, ATile* Tile);

	ATile* GetTile(int32 I, int32 J) const;

	ATile* GetNeighborTile(const ATile* Tile, ESwipeDirection NeighborDirection) const;
};
