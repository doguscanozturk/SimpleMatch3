#pragma once
#include <vector>
#include "MatchIdentity.h"
#include "Matrix/MatchMatrix.h"
#include "Match.generated.h"

using namespace std;

UCLASS(Abstract)
class UMatch : public UObject
{
	GENERATED_BODY()

public:
	virtual void Initialize();
	
	virtual int GetMinPieceRequirement();
	
	FMatchIdentity Check(std::vector<APiece*> MatchingPieces);

protected:	
	UPROPERTY(VisibleAnywhere)
	TArray<FMatchMatrix> MatrixChoreographies;

	vector<APiece*> ValidPiecesCache;

	virtual FMatchMatrix GetChoreography();
	
	void InitializeChoreography(FMatchMatrix Choreography);
};
