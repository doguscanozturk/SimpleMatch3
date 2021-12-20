#pragma once
#include "BasicMatch3ToolProvider.h"
#include "Grid/TileGrid.h"
#include "InitialMatchRemover.generated.h"

UCLASS()
class UInitialMatchRemover : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(UBasicMatch3ToolProvider* basicMatch3ToolProvider);

	void Clear();
	
	void RemoveInitialMatches(UTileGrid* TileGrid);

	void ChangeMidElementWithDifferentPiece(TArray<APiece*>& MatchingPieces, const UTileGrid* TileGrid) const;

protected:
	UPROPERTY()
	UBasicMatch3ToolProvider* BasicMatch3ToolProvider;
};
