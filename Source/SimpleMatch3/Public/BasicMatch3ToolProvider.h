#pragma once
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
	void Initialize(const UBlueprintReferences* BlueprintReferences);
	
	void Uninitialize();

	void Clear();

	UPROPERTY(VisibleAnywhere)
	ABezierMovementManager* BezierMovementManager;
	
	UPROPERTY(VisibleAnywhere)
	UMatchIdentifier* MatchIdentifier;
	
	UPROPERTY(VisibleAnywhere)
	UMatchFinder* MatchFinder;
	
	UPROPERTY(VisibleAnywhere)
	UPieceGenerator* PieceGenerator;
};
