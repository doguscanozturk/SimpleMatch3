#pragma once
#include "Tile.h"
#include "TileGrid.h"
#include "DataAssets/BlueprintReferences.h"
#include "Pieces/PieceGenerator.h"
#include "GridGenerator.generated.h"

UCLASS()
class UGridGenerator : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize(UPieceGenerator* pieceGenerator, UBlueprintReferences* blueprintReferences);

	void Clear();
	
	UTileGrid* Generate(FIntPoint Size);
	
private:
	UPROPERTY()
	UPieceGenerator* PieceGenerator;
	
	UPROPERTY()
	UBlueprintReferences* BlueprintReferences;

	ATile* SpawnGridTile(FVector Position, FRotator Rotation, int I, int J);
};
