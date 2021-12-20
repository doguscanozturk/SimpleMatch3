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
	DECLARE_DELEGATE_OneParam(FOnTargetsInitialized, std::vector<UTargetData*>)
	FOnTargetsInitialized OnTargetsInitialized;
	
	DECLARE_DELEGATE_OneParam(FOnTargetUpdated, const UTargetData*)
	FOnTargetUpdated OnATargetUpdated;
	
	DECLARE_DELEGATE_OneParam(FOnATargetComplete, const UTargetData*)
	FOnATargetComplete OnATargetComplete;
	
	DECLARE_DELEGATE(FOnAllTargetsComplete)
	FOnAllTargetsComplete OnAllTargetsComplete;
	
	void Initialize(ABoardFlowManager* BoardFlowManager);
	
	void Clear();

	void LoadRandomTargets();
	
	void HandlePiecesDestroyed(vector<EPieceType> Types);
	
	void CheckIsAllTargetsComplete();
	
private:
	vector<UTargetData*> ActiveTargets;
};
