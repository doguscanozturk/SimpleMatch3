#pragma once
#include "BezierSegment.h"
#include "IBezierMovementUser.h"
#include "BezierMovement.generated.h"

UCLASS()
class UBezierMovement : public UObject
{
	GENERATED_BODY()
	
public:
	DECLARE_EVENT(UBezierMovement, FOnComplete);
	FOnComplete OnComplete;

	UPROPERTY()
	bool IsDirty;
	
	void Initialize(const FBezierSegment& segment, const float duration, const TScriptInterface<IBezierMovementUser> bezierMovementUser);
		
	void Advance(float DeltaTime);
	
	void UpdatePosition();

	void SetComplete();
	
	float GetPercentage() const;
	
	bool GetIsComplete() const;

	TScriptInterface<IBezierMovementUser> GetUser() const;
	
private:
	UPROPERTY()
	float TotalDuration;
	
	UPROPERTY()
	float CurrentDuration;
	
	UPROPERTY()
	bool IsComplete;

	UPROPERTY()
	TScriptInterface<IBezierMovementUser> User;

	UPROPERTY()
	FBezierSegment Segment;
};
