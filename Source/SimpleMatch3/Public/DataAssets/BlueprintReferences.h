#pragma once
#include "Grid/Tile.h"
#include "BlueprintReferences.generated.h"

UCLASS()
class UBlueprintReferences : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> GridTileBP;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> PieceBP;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BoardFlowManagerBP;
	
	UPROPERTY(EditAnywhere)
	UDataAsset* PieceSettings;
};
