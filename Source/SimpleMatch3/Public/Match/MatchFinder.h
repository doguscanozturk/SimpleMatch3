#pragma once
#include <vector>
#include <unordered_set>
#include "Grid/TileGrid.h"
#include "Pieces/Piece.h"
#include "MatchFinder.generated.h"

using namespace std;

UCLASS()
class UMatchFinder : public UObject
{
	GENERATED_BODY()
	
public:
	void Clear();
	
	vector<APiece*> TryFindLocalMatch(UTileGrid* TileGrid, ATile* StartingNode);
	
	vector<vector<APiece*>> TryFindAllMatches(UTileGrid* TileGrid);
	
private:
	vector<APiece*> MatchingPiecesCache;
	
	unordered_set<ATile*> VisitedTilesCache;
	
	unordered_set<APiece*> MatchingPiecesCacheForFindingAllMatches;

	vector<APiece*> Empty;

	void CheckNode(UTileGrid* TileGrid, ATile* Tile, EPieceType SearchingPieceType,
	               unordered_set<ATile*>& VisitedTiles, vector<APiece*>& MatchingPiece);
};
