#include "TargetSystem/Match3TargetManager.h"
#include "Pieces/PieceHelpers.h"
#include "ThirdParty/boolinq.h"

void UMatch3TargetManager::Initialize(ABoardFlowManager* BoardFlowManager)
{
	BoardFlowManager->OnPiecesDestroyed.AddUObject(this, &UMatch3TargetManager::HandlePiecesDestroyed);
}

void UMatch3TargetManager::Clear()
{
	OnTargetsInitialized.Clear();
	OnATargetUpdated.Clear();
	OnATargetComplete.Clear();
	OnAllTargetsComplete.Clear();

	ActiveTargets.clear();
}

void UMatch3TargetManager::LoadRandomTargets()
{
	constexpr int8 TargetAmount = 3;
	for (int i = 0; i < TargetAmount; ++i)
	{
		EPieceType RandomPieceType;
		do
		{
			RandomPieceType = PieceHelpers::GetRandomPieceType();
		}
		while (boolinq::from(ActiveTargets).any([RandomPieceType](const TWeakObjectPtr<UTargetData> TargetData)
		{
			return TargetData->Type == RandomPieceType;
		}));

		const auto NewTargetData = NewObject<UTargetData>(this);
		NewTargetData->Type = RandomPieceType;
		NewTargetData->Amount = FMath::RandRange(10, 20);
		ActiveTargets.push_back(NewTargetData);
	}

	OnTargetsInitialized.Broadcast(ActiveTargets);
}

void UMatch3TargetManager::HandlePiecesDestroyed(vector<EPieceType> Types)
{
	auto DestroyedType = Types[0];
	const auto AnyTargetWithThatType = boolinq::from(ActiveTargets).any([DestroyedType](const TWeakObjectPtr<UTargetData> Target)
	{
		if (!Target.IsValid())
		{
			return false;
		}
		return Target->Type == DestroyedType;
	});

	if (!AnyTargetWithThatType)
	{
		return;
	}

	const auto Target = boolinq::from(ActiveTargets).first([DestroyedType](const TWeakObjectPtr<UTargetData> Target)
	{
		if (!Target.IsValid())
		{
			return false;
		}
		return Target->Type == DestroyedType;
	});

	if (Target->IsComplete())
	{
		return;
	}

	Target->Amount -= Types.size();
	if (Target->Amount <= 0)
	{
		Target->Amount = 0;
		OnATargetComplete.Broadcast(Target);
		CheckIsAllTargetsComplete();
	}
	else
	{
		OnATargetUpdated.Broadcast(Target);
	}
}

void UMatch3TargetManager::CheckIsAllTargetsComplete()
{
	const auto IsAllComplete = boolinq::from(ActiveTargets).all([](const TWeakObjectPtr<UTargetData> Target)
	{
		if (!Target.IsValid())
		{
			return false;
		}
		return Target->Amount <= 0;
	});

	if (IsAllComplete)
	{
		OnAllTargetsComplete.Broadcast();
	}
}
