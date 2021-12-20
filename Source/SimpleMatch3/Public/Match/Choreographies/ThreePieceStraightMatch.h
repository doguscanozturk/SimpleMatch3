#pragma once
#include "Match/Match.h"
#include "Match/Matrix/MatchMatrix.h"
#include "ThreePieceStraightMatch.generated.h"

UCLASS()
class UThreePieceStraightMatch : public UMatch
{
	GENERATED_BODY()
	
public:
	virtual int GetMinPieceRequirement() override;
	
	virtual void Initialize() override;
	
protected:
	virtual FMatchMatrix GetChoreography() override;
};
