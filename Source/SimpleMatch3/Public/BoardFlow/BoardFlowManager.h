#pragma once
#include "BasicMatch3ToolProvider.h"
#include "Controllers/GridController.h"
#include "Controllers/SwipeDirection.h"
#include "Grid/Tile.h"
#include "Grid/TileGrid.h"
#include "BoardFlowManager.generated.h"

UCLASS()
class ABoardFlowManager : public AActor
{
	GENERATED_BODY()
public:
	ABoardFlowManager();
	
	void Initialize(UTileGrid* tileGrid, UBasicMatch3ToolProvider* basicMatch3ToolProvider, AGridController* gridController);

	void Clear();

	DECLARE_DELEGATE_OneParam(FOnPiecesDestroyed, vector<EPieceType>)
	FOnPiecesDestroyed OnPiecesDestroyed;
	
protected:
	UPROPERTY()
	UTileGrid* TileGrid;
	
	UPROPERTY()
	UBasicMatch3ToolProvider* BasicMatch3ToolProvider;

	void MovePiece(ATile* StartTile, ATile* EndTile, float Duration, APiece* Piece) const;
	
	void TrySwapTiles(ATile* Tile, ESwipeDirection Direction);

	void SwapTiles(ATile* TileA, ATile* TileB, bool CanTriggerRevertSwap);

	/** Starts checking from CheckTile and returns true if it finds a match.*/
	bool CheckMatch(ATile* CheckTile) const;

	void OnTileIsEmpty(ATile* Tile) const;

	void OnTilesAreEmpty(vector<ATile*> Tiles) const;

	void OnPieceMovementCompleted(ATile* Tile, APiece* Piece) const;

	void GenerateNewPieceFromPeak(ATile* PeakTile) const;
};
