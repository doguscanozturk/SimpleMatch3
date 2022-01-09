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

	void Uninitialize();

	DECLARE_EVENT_OneParam(ABoardFlowManager, FOnPiecesDestroyed, vector<EPieceType>)
	FOnPiecesDestroyed OnPiecesDestroyed;
	
protected:
	UPROPERTY()
	UTileGrid* TileGrid;
	
	UPROPERTY()
	UBasicMatch3ToolProvider* BasicMatch3ToolProvider;

	UPROPERTY()
	TArray<FTimerHandle> ActiveTimerHandles;
	
	bool IsInitialized;
	
	void MovePiece(ATile* StartTile, ATile* EndTile, float Duration, APiece* Piece);
	
	void TrySwapTiles(ATile* Tile, ESwipeDirection Direction);

	void SwapTiles(ATile* TileA, ATile* TileB, bool CanTriggerRevertSwap);
	
	/** Starts checking from CheckTile and returns true if it finds a match.*/
	bool TryIdentifyAndExecuteMatch(ATile* CheckTile);

	void TryPullPieceOfTopTile(ATile* Tile);
	
	void GenerateNewPieceIfTileIsAtPeak(ATile* Tile);

	void OnTilesAreEmpty(vector<ATile*> Tiles);

	void OnPieceMovementCompleted(ATile* Tile, APiece* Piece);

	void GenerateNewPieceFromPeak(ATile* PeakTile);
};
