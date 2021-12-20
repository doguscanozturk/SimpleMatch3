#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pieces/Piece.h"
#include "PaperSpriteComponent.h"
#include "Tile.generated.h"

UCLASS()
class SIMPLEMATCH3_API ATile : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	int32 I;
	
	UPROPERTY(VisibleAnywhere)
	int32 J;
	
	UPROPERTY(VisibleAnywhere)
	APiece* AttachedPiece;
	
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UPaperSpriteComponent> SpriteRenderer;
	
	UPROPERTY(VisibleAnywhere)
	bool IsTargetedByMovingPiece;

	ATile();

	void Clear();
	
	void AttachPiece(APiece* Piece, bool ShouldUpdatePositionInstantly = false);
	
	APiece* DetachPiece();
};
