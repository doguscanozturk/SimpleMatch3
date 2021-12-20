#include "TargetSystem/Match3TargetManager.h"
#include "Pieces/PieceHelpers.h"
#include "ThirdParty/boolinq.h"

void UMatch3TargetManager::Initialize(ABoardFlowManager* BoardFlowManager)
{
	BoardFlowManager->OnPiecesDestroyed.BindUObject(this, &UMatch3TargetManager::HandlePiecesDestroyed);
}

void UMatch3TargetManager::Clear()
{
	OnTargetsInitialized.Unbind();
	OnATargetUpdated.Unbind();
	OnATargetComplete.Unbind();
	OnAllTargetsComplete.Unbind();
	
	ActiveTargets.clear();
}

void UMatch3TargetManager::LoadRandomTargets()
{
	ActiveTargets.clear();
	constexpr int8 TargetAmount = 3;

	for (int i = 0; i < TargetAmount; ++i)
	{
		EPieceType RandomPieceType;
		do
		{
			RandomPieceType = PieceHelpers::GetRandomPieceType();
		}
		while (boolinq::from(ActiveTargets).any([RandomPieceType](const UTargetData* TargetData)
		{
			return TargetData->Type == RandomPieceType;
		}));

		auto NewTargetData = NewObject<UTargetData>();
		NewTargetData->Type = RandomPieceType;
		NewTargetData->Amount = FMath::RandRange(10, 20);
		ActiveTargets.push_back(NewTargetData);
	}

	(void)OnTargetsInitialized.ExecuteIfBound(ActiveTargets);
}

void UMatch3TargetManager::HandlePiecesDestroyed(vector<EPieceType> Types)
{
	auto DestroyedType = Types[0];
	const auto AnyTargetWithThatType = boolinq::from(ActiveTargets).any([DestroyedType](const UTargetData* Target)
	{
		return Target->Type == DestroyedType;
	});

	if (!AnyTargetWithThatType)
	{
		return;
	}

	const auto Target = boolinq::from(ActiveTargets).first([DestroyedType](const UTargetData* Target)
	{
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
		(void)OnATargetComplete.ExecuteIfBound(Target);
		CheckIsAllTargetsComplete();
	}
	else
	{
		(void)OnATargetUpdated.ExecuteIfBound(Target);
	}
}

void  UMatch3TargetManager::CheckIsAllTargetsComplete()
{
	const auto IsAllComplete = boolinq::from(ActiveTargets).all([](const UTargetData* Target)
	{
		return Target->Amount <= 0;
	});

	if(IsAllComplete)
	{
		(void)OnAllTargetsComplete.ExecuteIfBound();
	}
}
