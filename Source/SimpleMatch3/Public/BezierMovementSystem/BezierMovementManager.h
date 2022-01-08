#pragma once
#include <vector>
#include "CoreMinimal.h"
#include "BezierMovement.h"
#include "GameFramework/Actor.h"
#include "BezierMovementManager.generated.h"

UCLASS()
class SIMPLEMATCH3_API ABezierMovementManager : public AActor
{
	GENERATED_BODY()

public:
	ABezierMovementManager();

	virtual void Tick(float DeltaTime) override;

	UBezierMovement* StartMovement(const FBezierSegment& BezierSegment, float Duration, TScriptInterface<IBezierMovementUser> User);

	UBezierMovement* StartMovement(FVector StartPoint, FVector EndPoint, float Duration, TScriptInterface<IBezierMovementUser> User);

	UBezierMovement* StartMovement(FVector StartPoint, FVector EndPoint, FVector ControlPoint,
	                               float Duration, TScriptInterface<IBezierMovementUser> User);

	UBezierMovement* StartMovement(FVector StartPoint, FVector EndPoint, FVector ControlPointOne, FVector ControlPointTwo,
	                               float Duration, TScriptInterface<IBezierMovementUser> User);
	
	void Clear();

private:
	std::vector<UBezierMovement*> ActiveMovements;

	FBezierSegment CreateSegment(const FVector StartPoint, const FVector EndPoint);
};
