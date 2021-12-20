#pragma once
#include "Match/Match.h"
#include "Match/Matrix/MatchMatrix.h"
#include "FourPieceStraightMatch.generated.h"

UCLASS()
class UFourPieceStraightMatch : public UMatch
{
	GENERATED_BODY()
	
public:
	virtual int GetMinPieceRequirement() override;
	
	virtual void Initialize() override;
	
protected:
	virtual FMatchMatrix GetChoreography() override;
};
