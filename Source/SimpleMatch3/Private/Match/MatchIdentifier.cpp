#include "Match/MatchIdentifier.h"
#include "Match/MatchIdentity.h"
#include "Match/Choreographies/FivePieceLMatch.h"
#include "Match/Choreographies/FivePieceStraightMatch.h"
#include "Match/Choreographies/FivePieceTMatch.h"
#include "Match/Choreographies/FourPieceSquareMatch.h"
#include "Match/Choreographies/FourPieceStraightMatch.h"
#include "Match/Choreographies/ThreePieceStraightMatch.h"
#include "Match/Exceptions/NoMatchFoundException.h"

UMatchIdentifier::UMatchIdentifier()
{
	PossibleMatchShapesInCheckOrder = {
		NewObject<UFivePieceTMatch>(),
		NewObject<UFivePieceLMatch>(),
		NewObject<UFivePieceStraightMatch>(),
		NewObject<UFourPieceStraightMatch>(),
		NewObject<UFourPieceSquareMatch>(),
		NewObject<UThreePieceStraightMatch>()
	};

	for (const auto Match : PossibleMatchShapesInCheckOrder)
	{
		Match->Initialize();
	}
}

void UMatchIdentifier::Clear()
{
	
}

vector<FMatchIdentity> UMatchIdentifier::Identify(const std::vector<APiece*>& MatchingPieces)
{
	MatchedPiecesCache.Empty();
	MatchIdentitiesCache.Empty();

	vector<FMatchIdentity> MatchIdentities;

	for (int i = 0; i < PossibleMatchShapesInCheckOrder.Num(); i++)
	{
		FMatchIdentity MatchIdentity;
		try
		{
			MatchIdentity = PossibleMatchShapesInCheckOrder[i]->CheckShape(MatchingPieces);
		}
		catch (NoMatchFoundException)
		{
			continue;
		}

		// auto ClassName = PossibleMatchesInCheckOrder[i]->GetClass()->GetName();
		// DEBUG("%s Match found!", *ClassName);

		MatchIdentitiesCache.Add(MatchIdentity);
		for (int j = 0; j < MatchIdentity.Pieces.Num(); ++j)
		{
			MatchedPiecesCache.Remove(MatchIdentity.Pieces[j]);
		}
		MatchIdentities.push_back(MatchIdentity);

		if (MatchedPiecesCache.Num() < 3)
		{
			break;
		}
	}

	return MatchIdentities;
}

vector<FMatchIdentity> UMatchIdentifier::IdentifyPlural(vector<vector<APiece*>> MatchingPieceLists)
{
	vector<FMatchIdentity> MatchIdentities;

	for (auto MatchingPieces : MatchingPieceLists)
	{
		auto Identities = Identify(MatchingPieces);

		for (auto Identity : Identities)
		{
			MatchIdentities.push_back(Identity);
		}

	}
	
	return MatchIdentities;
}
