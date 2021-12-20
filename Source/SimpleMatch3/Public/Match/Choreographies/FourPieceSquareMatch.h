#pragma once
#include "Match/Match.h"

#include "FourPieceSquareMatch.generated.h"

UCLASS()
class UFourPieceSquareMatch : public UMatch
{
	GENERATED_BODY()
	
public:
	virtual int GetMinPieceRequirement() override;
	
	virtual void Initialize() override;
	
protected:
	virtual FMatchMatrix GetChoreography() override;
};
