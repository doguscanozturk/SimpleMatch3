#pragma once
#include "Match/Match.h"
#include "FivePieceTMatch.generated.h"

UCLASS()
class UFivePieceTMatch : public UMatch
{
	GENERATED_BODY()
	
public:
	virtual void Initialize() override;
	
	virtual int GetMinPieceRequirement() override;

protected:
	virtual FMatchMatrix GetChoreography() override;
};
