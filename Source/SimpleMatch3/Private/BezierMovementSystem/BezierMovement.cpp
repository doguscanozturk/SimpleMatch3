#include "BezierMovementSystem/BezierMovement.h"

#include "BezierMovementSystem/BezierFormulas.h"
#include "Kismet/KismetMathLibrary.h"
#include "TraceServices/Public/TraceServices/Containers/Timelines.h"
#include "Utility/TestMacros.h"

void UBezierMovement::Initialize(const FBezierSegment& segment, const float duration, const TScriptInterface<IBezierMovementUser> bezierMovementUser)
{
	Segment = segment;
	TotalDuration = duration;
	User = bezierMovementUser;
	CurrentDuration = 0;
	IsComplete = false;
}

float UBezierMovement::GetPercentage() const
{
	const auto CurrentPercentage = CurrentDuration / TotalDuration;
	return FMath::Clamp(CurrentPercentage, 0.f, 1.f);
}

bool UBezierMovement::GetIsComplete() const
{
	return IsComplete;
}

TScriptInterface<IBezierMovementUser> UBezierMovement::GetUser() const
{
	return User;
}

void UBezierMovement::Advance(float DeltaTime)
{
	CurrentDuration += DeltaTime;
}

void UBezierMovement::UpdatePosition()
{
	if (User == nullptr)
	{
		IsDirty = true;
		return;
	}

	const auto Percentage = GetPercentage();

	FVector Position;
	switch (Segment.Type)
	{
		case EBezierType::Linear:
			Position = BezierFormulas::Linear(Segment.StartPoint, Segment.EndPoint, Percentage);
			break;
		case EBezierType::Quadratic:
			Position = BezierFormulas::Quadratic(Segment.StartPoint, Segment.EndPoint, Segment.ControlPointOne, Percentage);
			break;
		case EBezierType::Cubic:
			Position = BezierFormulas::Cubic(Segment.StartPoint, Segment.EndPoint, Segment.ControlPointOne, Segment.ControlPointTwo, Percentage);
			break;
	}

	User->SetLocation(Position);
}

void UBezierMovement::SetComplete()
{
	IsComplete = true;
}
