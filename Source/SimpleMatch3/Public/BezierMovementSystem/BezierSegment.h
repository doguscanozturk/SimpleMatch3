#pragma once
#include "BezierType.h"
#include "BezierSegment.generated.h" 

USTRUCT(BlueprintType)
struct FBezierSegment
{
	GENERATED_BODY()

	UPROPERTY()
	FVector StartPoint;
	
	UPROPERTY()
	FVector EndPoint;
	
	UPROPERTY()
	FVector ControlPointOne;
	
	UPROPERTY()
	FVector ControlPointTwo;
	
	UPROPERTY()
	float Length;

	UPROPERTY()
	EBezierType Type;
};