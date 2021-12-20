#pragma once
#include <vector>
#include "Match.h"
#include "MatchIdentity.h"
#include "Pieces/Piece.h"
#include "MatchIdentifier.generated.h"

using namespace std;

UCLASS()
class UMatchIdentifier : public UObject
{
public:
	GENERATED_BODY()
	
	UMatchIdentifier();
	
	void Clear();
	
	vector<FMatchIdentity> Identify(const std::vector<APiece*>& MatchingPieces);
	
	vector<FMatchIdentity> IdentifyPlural(vector<vector<APiece*>> MatchingPieceLists);

private:
	UPROPERTY()
	TArray<APiece*> MatchedPiecesCache;
	
	UPROPERTY()
	TArray<FMatchIdentity> MatchIdentitiesCache;
	
	UPROPERTY()
	TArray<UMatch*> PossibleMatchesInCheckOrder;
};
