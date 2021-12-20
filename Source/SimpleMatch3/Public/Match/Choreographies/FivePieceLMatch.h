#pragma once

#include "Match/Match.h"
#include "Match/Matrix/MatchMatrix.h"
#include "FivePieceLMatch.generated.h"

UCLASS()
class UFivePieceLMatch : public UMatch
{
	GENERATED_BODY()
	
public:
	virtual void Initialize() override;
	
	virtual int GetMinPieceRequirement() override;

protected:
	virtual FMatchMatrix GetChoreography() override;
};
