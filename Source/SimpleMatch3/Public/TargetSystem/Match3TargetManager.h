#pragma once
#include <vector>
#include "BoardFlow/BoardFlowManager.h"
#include "Match3TargetManager.generated.h"

UCLASS()
class UTargetData : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	EPieceType Type;
	
	UPROPERTY(EditAnywhere)
	int8 Amount;

	bool IsComplete() const
	{
		return Amount <= 0;
	}
};

UCLASS()
class UMatch3TargetManager : public UObject
{
	GENERATED_BODY()
	
public:
	DECLARE_EVENT_OneParam(UMatch3TargetManager, FOnTargetsInitialized, std::vector<TWeakObjectPtr<UTargetData>>)
	FOnTargetsInitialized OnTargetsInitialized;
	
	DECLARE_EVENT_OneParam(UMatch3TargetManager, FOnTargetUpdated, const TWeakObjectPtr<UTargetData>)
	FOnTargetUpdated OnATargetUpdated;
	
	DECLARE_EVENT_OneParam(UMatch3TargetManager, FOnATargetComplete, const TWeakObjectPtr<UTargetData>)
	FOnATargetComplete OnATargetComplete;
	
	DECLARE_EVENT(UMatch3TargetManager, FOnAllTargetsComplete)
	FOnAllTargetsComplete OnAllTargetsComplete;
	
	void Initialize(ABoardFlowManager* BoardFlowManager);
	
	void Clear();

	void LoadRandomTargets();
	
	void HandlePiecesDestroyed(vector<EPieceType> Types);
	
	void CheckIsAllTargetsComplete();
	
private:
	vector<TWeakObjectPtr<UTargetData>> ActiveTargets;
};
