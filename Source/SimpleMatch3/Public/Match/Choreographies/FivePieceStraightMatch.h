#pragma once
#include "Match/Match.h"
#include "FivePieceStraightMatch.generated.h"

UCLASS()
class UFivePieceStraightMatch : public UMatch
{
	GENERATED_BODY()
	
public:
	virtual void Initialize() override;
	
	virtual int GetMinPieceRequirement() override;

protected:
	virtual FMatchMatrix GetChoreography() override;
};
