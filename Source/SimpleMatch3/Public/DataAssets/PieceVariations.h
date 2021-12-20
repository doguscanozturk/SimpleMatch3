#pragma once
#include "Pieces/Piece.h"
#include "PieceVariations.generated.h"

UCLASS(BlueprintType)
class UPieceVariations : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FPieceData> Variations;

	static std::tuple<bool, FPieceData> TryGetPieceData(const TArray<FPieceData>& PieceVariations, const EPieceType DesiredType)
	{
		for (auto PieceData : PieceVariations)
		{
			if(PieceData.Type == DesiredType)
			{
				return std::make_tuple(true, PieceData);
			}
		}

		return std::make_tuple(false, FPieceData::Empty());
	}
};