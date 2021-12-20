#include "Pieces/Piece.h"

APiece::APiece()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void APiece::BeginPlay()
{
	Super::BeginPlay();
	SpriteRenderer = Cast<UPaperSpriteComponent>(GetComponentByClass(UPaperSpriteComponent::StaticClass()));
}

void APiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ScaleTimeline.TickTimeline(DeltaTime);
	BounceTimeline.TickTimeline(DeltaTime);
	FadeInTimeline.TickTimeline(DeltaTime);
}


void APiece::Set(FPieceData settings)
{
	this->Settings = settings;
	SpriteRenderer->SetSprite(Settings.Sprite);
}

void APiece::SetParentIndex(int32 parentI, int32 parentJ)
{
	this->ParentI = parentI;
	this->ParentJ = parentJ;
}

void APiece::SetLocation(const FVector Location)
{
	SetActorLocation(Location);
}

void APiece::TriggerScaleDownAndDestroy()
{
	IsPlayingMatchAnimation = true;
	FOnTimelineFloat OnScaleTimelineFloatUpdate;
	OnScaleTimelineFloatUpdate.BindDynamic(this, &APiece::SetScale);
	ScaleTimeline.AddInterpFloat(ScaleDownCurve, OnScaleTimelineFloatUpdate);
	
	// FOnTimelineEvent OnScaleTimelineComplete;
	// OnScaleTimelineComplete.BindDynamic(this, &APiece::DestroySelf);
	// ScaleTimeline.SetTimelineFinishedFunc(OnScaleTimelineComplete);

	ScaleTimeline.ReverseFromEnd();
}

void APiece::TriggerBounce()
{
	FOnTimelineFloat OnBounceTimelineUpdate;
	OnBounceTimelineUpdate.BindDynamic(this, &APiece::SetRelativePosition);
	BounceTimeline.AddInterpFloat(BounceCurve, OnBounceTimelineUpdate);
	BounceTimeline.PlayFromStart();
}

void APiece::TriggerFadeIn()
{
	FOnTimelineFloat OnFadeInUpdate;
	OnFadeInUpdate.BindDynamic(this, &APiece::SetSpriteAlpha);
	FadeInTimeline.AddInterpFloat(FadeInCurve, OnFadeInUpdate);
	FadeInTimeline.PlayFromStart();
}

bool APiece::IsAvailableToPullDown() const
{
	return !IsPlayingMatchAnimation;
}

float APiece::GetScaleDownAnimationDuration() const
{
	return ScaleDownCurve->FloatCurve.GetLastKey().Time;
}

void APiece::SetRelativePosition(float Percentage)
{
	const FVector NewPosition = FVector::UpVector * (Percentage * 400);
	SetActorRelativeLocation(NewPosition);
}

void APiece::SetScale(float Percentage)
{
	SetActorScale3D(FVector::OneVector * Percentage);
}

void APiece::SetSpriteAlpha(float Percentage)
{
	auto CurrentColor = SpriteRenderer->GetSpriteColor();
	CurrentColor.A = Percentage;
	SpriteRenderer->SetSpriteColor(CurrentColor);
}

void APiece::DestroySelf()
{
	Destroy();
}
