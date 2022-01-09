#pragma once
class UInitialMatchRemover;
#include "Grid/GridGenerator.h"
#include "BezierMovementSystem/BezierMovementManager.h"
#include "DataAssets/BlueprintReferences.h"
#include "Pieces/PieceGenerator.h"
#include "Match/MatchFinder.h"
#include "Match/MatchIdentifier.h"
#include "BasicMatch3ToolProvider.generated.h"

UCLASS()
class UBasicMatch3ToolProvider : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize(UBlueprintReferences* BlueprintReferences);
	
	void Uninitialize();

	void Clear() const;

	UPROPERTY(VisibleAnywhere)
	ABezierMovementManager* BezierMovementManager;
	
	UPROPERTY(VisibleAnywhere)
	UMatchIdentifier* MatchIdentifier;
	
	UPROPERTY(VisibleAnywhere)
	UMatchFinder* MatchFinder;
	
	UPROPERTY(VisibleAnywhere)
	UPieceGenerator* PieceGenerator;

	UPROPERTY()
	UGridGenerator* GridGenerator;
	
	UPROPERTY()
	UInitialMatchRemover* InitialMatchRemover;
};
