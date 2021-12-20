#include "Match/MatchFinder.h"

void UMatchFinder::Clear()
{
	
}

vector<APiece*> UMatchFinder::TryFindLocalMatch(UTileGrid* TileGrid, ATile* StartingNode)
{
	if (StartingNode->AttachedPiece == nullptr)
	{
		return Empty;
	}

	auto SearchingType = StartingNode->AttachedPiece->Settings.Type;

	VisitedTilesCache.clear();
	MatchingPiecesCache.clear();

	CheckNode(TileGrid, StartingNode, SearchingType, VisitedTilesCache, MatchingPiecesCache);

	if (MatchingPiecesCache.size() >= 3)
	{
		const vector<APiece*> Result(MatchingPiecesCache.begin(), MatchingPiecesCache.end());
		return Result;
	}

	return Empty;
}

vector<vector<APiece*>> UMatchFinder::TryFindAllMatches(UTileGrid* TileGrid)
{
	MatchingPiecesCacheForFindingAllMatches.clear();
	
	vector<vector<APiece*>> Result;
	
	for(const auto Tile : TileGrid->Tiles)
	{
		if(MatchingPiecesCacheForFindingAllMatches.count(Tile->AttachedPiece) > 0)
		{
			continue;
		}
			
		auto MatchingPiece = TryFindLocalMatch(TileGrid, Tile);
		if(MatchingPiece.size() > 0)
		{
			for (int k = 0; k < MatchingPiece.size(); k++)
			{
				MatchingPiecesCacheForFindingAllMatches.insert(MatchingPiece[k]);
			}

			Result.push_back(MatchingPiece);
		}
	}

	return Result;
}

void UMatchFinder::CheckNode(UTileGrid* TileGrid, ATile* Tile, EPieceType SearchingPieceType,
                             unordered_set<ATile*>& VisitedTiles, vector<APiece*>& MatchingPieces)
{
	const auto CountOfTile = VisitedTiles.count(Tile);
	if (Tile == nullptr || Tile->AttachedPiece == nullptr || Tile->AttachedPiece->Settings.Type != SearchingPieceType || CountOfTile == 1
		|| Tile->AttachedPiece->IsPlayingMatchAnimation)
	{
		return;
	}

	VisitedTiles.insert(Tile);
	MatchingPieces.push_back(Tile->AttachedPiece);

	auto TopTile = TileGrid->GetTile(Tile->I, Tile->J - 1);
	CheckNode(TileGrid, TopTile, SearchingPieceType, VisitedTiles, MatchingPieces);
	auto LeftTile = TileGrid->GetTile(Tile->I - 1, Tile->J);
	CheckNode(TileGrid, LeftTile, SearchingPieceType, VisitedTiles, MatchingPieces);
	auto BottomTile = TileGrid->GetTile(Tile->I, Tile->J + 1);
	CheckNode(TileGrid, BottomTile, SearchingPieceType, VisitedTiles, MatchingPieces);
	auto RightTile = TileGrid->GetTile(Tile->I + 1, Tile->J);
	CheckNode(TileGrid, RightTile, SearchingPieceType, VisitedTiles, MatchingPieces);
}
