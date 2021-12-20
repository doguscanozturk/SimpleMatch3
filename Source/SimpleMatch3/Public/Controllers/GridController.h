#pragma once
#include "CoreMinimal.h"
#include "SwipeDirection.h"
#include "GameFramework/PlayerController.h"
#include "Grid/Tile.h"
#include "GridController.generated.h"

UCLASS()
class SIMPLEMATCH3_API AGridController : public APlayerController
{
	GENERATED_BODY()
	
public:
	DECLARE_DELEGATE_TwoParams(FOnSwipeApproved, ATile*, ESwipeDirection)
	FOnSwipeApproved OnSwipeApproved;

	DECLARE_DELEGATE_OneParam(FOnTileTouched, ATile*)
	FOnTileTouched OnTileTouched;
	
	AGridController(const FObjectInitializer& ObjectInitializer);

	void Clear();
	
	virtual void SetupInputComponent() override;
	
protected:
	bool IsLocked;

	bool IsDragDetectedOnce;

	FVector TouchStartPosition;

	UPROPERTY()
	ATile* LastTouchedTile;
	
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector TouchLocation);
	
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
	
	void OnDrag(ETouchIndex::Type FingerIndex, FVector Location);
};
