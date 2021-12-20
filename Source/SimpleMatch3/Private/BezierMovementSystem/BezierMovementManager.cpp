#include "BezierMovementSystem/BezierMovementManager.h"

ABezierMovementManager::ABezierMovementManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABezierMovementManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = ActiveMovements.size() - 1; i >= 0; i--)
	{
		const auto Bm = ActiveMovements[i];

		if (Bm->IsDirty)
		{
			ActiveMovements.erase(ActiveMovements.begin() + i);
			continue;
		}

		Bm->Advance(DeltaTime);
		Bm->UpdatePosition();

		if (Bm->GetPercentage() >= 1.f)
		{
			Bm->SetComplete();
			(void)Bm->OnComplete.ExecuteIfBound();
			ActiveMovements.erase(ActiveMovements.begin() + i);
		}
	}
}

UBezierMovement* ABezierMovementManager::StartMovement(const FBezierSegment& BezierSegment, const float Duration,
                                                       const TScriptInterface<IBezierMovementUser> User)
{
	const auto Movement = NewObject<UBezierMovement>();
	Movement->Initialize(BezierSegment, Duration, User);
	ActiveMovements.push_back(Movement);
	return Movement;
}

UBezierMovement* ABezierMovementManager::StartMovement(const FVector StartPoint, const FVector EndPoint, const float Duration,
                                                       const TScriptInterface<IBezierMovementUser> User)
{
	FBezierSegment Segment = CreateSegment(StartPoint, EndPoint);
	Segment.Type = EBezierType::Linear;
	return StartMovement(Segment, Duration, User);
}

UBezierMovement* ABezierMovementManager::StartMovement(FVector StartPoint, FVector EndPoint, FVector ControlPoint, float Duration,
                                                       TScriptInterface<IBezierMovementUser> User)
{
	FBezierSegment Segment = CreateSegment(StartPoint, EndPoint);
	Segment.Type = EBezierType::Quadratic;
	return StartMovement(Segment, Duration, User);
}

UBezierMovement* ABezierMovementManager::StartMovement(FVector StartPoint, FVector EndPoint, FVector ControlPointOne, FVector ControlPointTwo,
                                                       float Duration, TScriptInterface<IBezierMovementUser> User)
{
	FBezierSegment Segment = CreateSegment(StartPoint, EndPoint);
	Segment.Type = EBezierType::Cubic;
	return StartMovement(Segment, Duration, User);
}

void ABezierMovementManager::Clear()
{
	ActiveMovements.clear();
}

FBezierSegment ABezierMovementManager::CreateSegment(const FVector StartPoint, const FVector EndPoint)
{
	FBezierSegment Segment;
	Segment.StartPoint = StartPoint;
	Segment.EndPoint = EndPoint;
	Segment.Length = FVector::Dist(Segment.StartPoint, Segment.EndPoint);
	return Segment;
}
