#include "Controllers/GridController.h"
#include "DrawDebugHelpers.h"
#include "Constants/UXConstants.h"
#include "Controllers/SwipeDirection.h"
#include "Grid/Tile.h"
#include "Kismet/KismetMathLibrary.h"

AGridController::AGridController(const FObjectInitializer& ObjectInitializer)
{
	bShowMouseCursor = true;
	bEnableTouchEvents = bEnableClickEvents = true;
	bEnableTouchOverEvents = bEnableMouseOverEvents = true;
}

void AGridController::Clear()
{
	InputComponent->ClearActionBindings();
	OnTileTouched.Unbind();
}

void AGridController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindTouch(IE_Pressed, this, &AGridController::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AGridController::TouchStopped);
	InputComponent->BindTouch(IE_Repeat, this, &AGridController::OnDrag);
}

void AGridController::TouchStarted(ETouchIndex::Type FingerIndex, FVector TouchLocation)
{
	if(IsLocked) return;
	
	IsDragDetectedOnce = false;
	TouchStartPosition = TouchLocation;

	FVector WorldLocation;
	FVector WorldDirection;
	DeprojectScreenPositionToWorld(TouchLocation.X, TouchLocation.Y, WorldLocation, WorldDirection);
	WorldLocation.Y = -1000;
	
	const FVector TraceStart(WorldLocation.X, WorldLocation.Y, WorldLocation.Z);
	const FVector TraceEnd(WorldLocation.X, WorldLocation.Y + 10000, WorldLocation.Z);
	
	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Pawn))
	{
		LastTouchedTile = Cast<ATile>(Hit.Actor.Get());
		if (LastTouchedTile)
		{
			(void) OnTileTouched.ExecuteIfBound(LastTouchedTile);
		}
	}
}

void AGridController::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
}

void AGridController::OnDrag(ETouchIndex::Type FingerIndex, FVector Location)
{
	if(IsDragDetectedOnce || IsLocked) return;

	const auto DifferenceX = TouchStartPosition.X - Location.X;
	
	if (UKismetMathLibrary::Abs(DifferenceX) >= UXConstants::SwipeApprovalThreshold)
	{
		IsDragDetectedOnce = true;
		const auto SwipeDirection = DifferenceX < 0 ? ESwipeDirection::Right : ESwipeDirection::Left;
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, StaticEnum<ESwipeDirection>()->GetValueAsString(SwipeDirection));
		(void) OnSwipeApproved.ExecuteIfBound(LastTouchedTile, SwipeDirection);
		
		return;
	}

	const auto DifferenceY = TouchStartPosition.Y - Location.Y;
	
	if (UKismetMathLibrary::Abs(DifferenceY) >= UXConstants::SwipeApprovalThreshold)
	{
		IsDragDetectedOnce = true;
		const auto SwipeDirection = DifferenceY < 0 ? ESwipeDirection::Down : ESwipeDirection::Up;
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, StaticEnum<ESwipeDirection>()->GetValueAsString(SwipeDirection));
		(void) OnSwipeApproved.ExecuteIfBound(LastTouchedTile, SwipeDirection);
	}
}
