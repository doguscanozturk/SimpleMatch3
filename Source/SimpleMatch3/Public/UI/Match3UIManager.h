#pragma once
#include "LevelEndPanel.h"
#include "TargetPanel.h"
#include "TargetSystem/Match3TargetManager.h"
#include "Match3UIManager.generated.h"

UCLASS()
class UMatch3UIManager : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize(UMatch3TargetManager* Match3TargetManager, UPieceVariations* pieceVariations);

	void Clear();
	
	void LoadPanels();
	
	void HandleTargetsInitialized(std::vector<UTargetData*> TargetDatas);
	
	void HandleATargetUpdated(const UTargetData* TargetData);
	
	void HandleATargetComplete(const UTargetData* TargetData);
	
	void HandleAllTargetsComplete();

private:
	UPROPERTY()
	UTargetPanel* TargetPanel;
	
	UPROPERTY()
	ULevelEndPanel* LevelEndPanel;
	
	UPROPERTY()
	UPieceVariations* PieceVariations;
};

