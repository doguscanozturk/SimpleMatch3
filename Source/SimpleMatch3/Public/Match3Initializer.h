#pragma once
#include "CoreMinimal.h"
#include "SimpleMatch3GameInstance.h"
#include "BoardFlow/BoardFlowManager.h"
#include "GameFramework/Actor.h"
#include "Grid/GridGenerator.h"
#include "Match/InitialMatchRemover.h"
#include "UI/Match3UIManager.h"
#include "Match3Initializer.generated.h"

UCLASS()
class SIMPLEMATCH3_API AMatch3Initializer : public AActor
{
	GENERATED_BODY()

public:
	AMatch3Initializer();

	void Initialize();

	void Uninitialize();

protected:
	UPROPERTY(EditAnywhere)
	FIntPoint GridSize;

	UPROPERTY(EditAnywhere)
	AActor* MainCamera;

	UPROPERTY()
	UTileGrid* TileGrid;
	
	UPROPERTY()
	UMatch3UIManager* UIManager;

	UPROPERTY()
	UMatch3TargetManager* TargetManager;

	UPROPERTY()
	USimpleMatch3GameInstance* GameInstance;

	UPROPERTY()
	ABoardFlowManager* BoardFlowManager;

	UPROPERTY()
	AGridController* GridController;

	UPROPERTY()
	bool IsInitialized;
	
	virtual void BeginPlay() override;

	void HandleRestartClicked();
};
