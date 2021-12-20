#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "BezierMovementSystem/IBezierMovementUser.h"
#include "PieceType.h"
#include "Components/TimelineComponent.h"
#include "Piece.generated.h"

USTRUCT(BlueprintType)
struct FPieceData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	EPieceType Type;

	UPROPERTY(EditAnywhere)
	UPaperSprite* Sprite;

	UPROPERTY(EditAnywhere)
	UTexture2D* Texture;

	static FPieceData Empty()
	{
		return FPieceData();
	}
};

UCLASS()
class SIMPLEMATCH3_API APiece : public AActor, public IBezierMovementUser
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* SpriteRenderer;
	
	UPROPERTY(VisibleAnywhere)
	FPieceData Settings;
	
	UPROPERTY()
	uint8 ParentI;
	
	UPROPERTY()
	uint8 ParentJ;

	bool IsPlayingMatchAnimation;
	
	APiece();

	virtual void SetLocation(FVector Location) override;

	void Set(FPieceData Settings);
	
	void SetParentIndex(int32 ParentI, int32 ParentJ);
	
	void TriggerScaleDownAndDestroy();
	
	void TriggerBounce();

	void TriggerFadeIn();

	bool IsAvailableToPullDown() const;
	
	float GetScaleDownAnimationDuration() const;
	
protected:
	UPROPERTY(EditAnywhere)
	UCurveFloat* ScaleDownCurve;
	
	UPROPERTY(EditAnywhere)
	UCurveFloat* BounceCurve;
	
	UPROPERTY(EditAnywhere)
	UCurveFloat* FadeInCurve;
	
	UPROPERTY()
	FTimeline ScaleTimeline;
	
	UPROPERTY()
	FTimeline BounceTimeline;
	
	UPROPERTY()
	FTimeline FadeInTimeline;
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetRelativePosition(float Percentage);
	
	UFUNCTION()
	void SetScale(float Percentage);
	
	UFUNCTION()
	void SetSpriteAlpha(float Percentage);
	
	UFUNCTION()
	void DestroySelf();
};
