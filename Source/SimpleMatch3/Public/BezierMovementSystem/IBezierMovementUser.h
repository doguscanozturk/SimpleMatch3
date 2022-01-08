#pragma once
#include "IBezierMovementUser.generated.h"

UINTERFACE()
class UBezierMovementUser : public UInterface
{
	GENERATED_BODY()
};

/** The interface for the objects that can be used by BezierMovementSystem. */
class IBezierMovementUser
{
	GENERATED_BODY()

public:
	
	virtual void SetLocation(FVector Location) = 0;

	virtual void OnAborted() = 0;
};
