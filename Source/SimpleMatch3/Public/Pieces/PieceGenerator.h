#pragma once
#include "Piece.h"
#include "PieceType.h"
#include "DataAssets/PieceVariations.h"
#include "PieceGenerator.generated.h"

UCLASS()
class UPieceGenerator : public UObject
{
	GENERATED_BODY()
	
public:	
	void Initialize(const TSubclassOf<AActor> pieceBP, UPieceVariations* pieceVariations);

	void Clear();
	
	APiece* GenerateRandom(FVector Position, FRotator Rotation) const;
	
	APiece* Generate(EPieceType Type, FVector Position, FRotator Rotation) const;

private:
	UPROPERTY()
	UPieceVariations* PieceVariations;

	UPROPERTY()
	TSubclassOf<APiece> PieceBP;
	
	FPieceData GetPieceData(EPieceType Type) const;
};