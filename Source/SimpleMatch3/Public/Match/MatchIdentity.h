#pragma once
#include "Pieces/Piece.h"
#include "MatchIdentity.generated.h"

USTRUCT()
struct FMatchIdentity
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<APiece*> Pieces;
};
