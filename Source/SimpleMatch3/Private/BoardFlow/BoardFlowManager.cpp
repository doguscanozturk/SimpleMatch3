#include "BoardFlow/BoardFlowManager.h"
#include "Kismet/GameplayStatics.h"
#include "Constants/GameplayConstants.h"
#include <vector>

using namespace std;

ABoardFlowManager::ABoardFlowManager()
{
}

void ABoardFlowManager::Initialize(UTileGrid* tileGrid, UBasicMatch3ToolProvider* basicMatch3ToolProvider, AGridController* gridController)
{
	IsInitialized = true;
	TileGrid = tileGrid;
	BasicMatch3ToolProvider = basicMatch3ToolProvider;
	gridController->OnSwipeApproved.AddUObject(this, &ABoardFlowManager::TrySwapTiles);
}

void ABoardFlowManager::Uninitialize()
{
	IsInitialized = false;
	OnPiecesDestroyed.Clear();

	for (auto TimerHandle : ActiveTimerHandles)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
	ActiveTimerHandles.Empty();

	BasicMatch3ToolProvider = nullptr;
	TileGrid = nullptr;
}

void ABoardFlowManager::TrySwapTiles(ATile* Tile, ESwipeDirection Direction)
{
	ATile* NeighborTile = TileGrid->GetNeighborTile(Tile, Direction);
	if (NeighborTile != nullptr)
	{
		SwapTiles(Tile, NeighborTile, true);
	}
}

void ABoardFlowManager::SwapTiles(ATile* TileA, ATile* TileB, const bool CanTriggerRevertSwap)
{
	const auto PieceA = TileA->DetachPiece();
	const auto PieceB = TileB->DetachPiece();

	TileA->AttachPiece(PieceB);
	TileB->AttachPiece(PieceA);

	const auto MovementA = BasicMatch3ToolProvider->BezierMovementManager->StartMovement(
		TileA->GetActorLocation(), TileB->GetActorLocation(), GameplayConstants::PieceSwapDuration, PieceA);

	const auto MovementB = BasicMatch3ToolProvider->BezierMovementManager->StartMovement(
		TileB->GetActorLocation(), TileA->GetActorLocation(), GameplayConstants::PieceSwapDuration, PieceB);

	if (CanTriggerRevertSwap)
	{
		MovementB->OnComplete.AddLambda([this, TileA, TileB]
		{
			if (!IsInitialized)
			{
				return;
			}

			FTimerHandle Handle;
			GetWorldTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([this, TileA, TileB, &Handle]
			{
				if (!IsInitialized)
				{
					return;
				}
				ActiveTimerHandles.Remove(Handle);

				const auto TileAHasIdentifiedMatch = TryIdentifyAndExecuteMatch(TileA);
				const auto TileBHasIdentifiedMatch = TryIdentifyAndExecuteMatch(TileB);

				if (!TileAHasIdentifiedMatch && !TileBHasIdentifiedMatch)
				{
					SwapTiles(TileB, TileA, false);
				}
			}), GameplayConstants::UnderstandabilityDelayAfterSwap, false);
			ActiveTimerHandles.Add(Handle);
		});
	}
}

bool ABoardFlowManager::TryIdentifyAndExecuteMatch(ATile* CheckTile)
{
	const vector<APiece*> LocalMatches = BasicMatch3ToolProvider->MatchFinder->TryFindLocalMatch(TileGrid, CheckTile);

	if (LocalMatches.size() > 0)
	{
		const vector<FMatchIdentity> IdentifiedMatches = BasicMatch3ToolProvider->MatchIdentifier->Identify(LocalMatches);

		if (IdentifiedMatches.size() > 0)
		{
			vector<ATile*> AffectedTiles;
			vector<EPieceType> AffectedPieceTypes;

			for (auto IM : IdentifiedMatches)
			{
				AffectedTiles.clear();

				for (const auto Piece : IM.Pieces)
				{
					const auto Tile = TileGrid->GetTile(Piece->ParentI, Piece->ParentJ);
					Tile->AttachedPiece->TriggerScaleDownAndDestroy();
					AffectedTiles.push_back(Tile);
					AffectedPieceTypes.push_back(Tile->AttachedPiece->Settings.Type);
				}

				FTimerHandle Handle;
				GetWorldTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([=]
				{
					ActiveTimerHandles.Remove(Handle);

					for (const auto Tile : AffectedTiles)
					{
						const auto DetachedPiece = Tile->DetachPiece();
						if (DetachedPiece != nullptr)
						{
							DetachedPiece->Destroy();
						}
					}

					OnPiecesDestroyed.Broadcast(AffectedPieceTypes);

					OnTilesAreEmpty(AffectedTiles);
				}), 0.2f + GameplayConstants::LengthOfAFrame60 * 2, false);
				ActiveTimerHandles.Add(Handle);
			}

			return true;
		}

		return false;
	}

	return false;
}

void ABoardFlowManager::TryPullPieceOfTopTile(ATile* Tile)
{
	if (!IsInitialized || Tile->IsTargetedByMovingPiece && Tile->AttachedPiece != nullptr)
	{
		return;
	}

	const auto TopTile = TileGrid->GetNeighborTile(Tile, ESwipeDirection::Up);
	if (TopTile != nullptr && TopTile->AttachedPiece != nullptr && TopTile->AttachedPiece->IsAvailableToPullDown())
	{
		const auto TopPiece = TopTile->DetachPiece();

		MovePiece(TopTile, Tile, GameplayConstants::PieceMoveDuration, TopPiece);

		FTimerHandle Handle;
		GetGameInstance()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([=]
		{
			ActiveTimerHandles.Remove(Handle);

			TryPullPieceOfTopTile(TopTile);
		}), GameplayConstants::DelayBeforePullingUpperTile, false);

		ActiveTimerHandles.Add(Handle);
	}

	GenerateNewPieceIfTileIsAtPeak(Tile);
}
void ABoardFlowManager::GenerateNewPieceIfTileIsAtPeak(ATile* Tile)
{
	if (Tile->I == 0)
	{
		FTimerHandle Handle;
		GetGameInstance()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([=]
		{
			ActiveTimerHandles.Remove(Handle);

			if (!Tile->IsTargetedByMovingPiece)
			{
				GenerateNewPieceFromPeak(Tile);
			}
		}), GameplayConstants::DelayBeforePullingUpperTile, false);

		ActiveTimerHandles.Add(Handle);
	}
}

void ABoardFlowManager::OnTilesAreEmpty(vector<ATile*> Tiles)
{
	for (const auto Tile : Tiles)
	{
		TryPullPieceOfTopTile(Tile);
	}
}

void ABoardFlowManager::OnPieceMovementCompleted(ATile* Tile, APiece* Piece)
{
	const auto BottomTile = TileGrid->GetNeighborTile(Tile, ESwipeDirection::Down);
	if (BottomTile != nullptr && !BottomTile->IsTargetedByMovingPiece && BottomTile->AttachedPiece == nullptr)
	{
		MovePiece(Tile, BottomTile, GameplayConstants::PieceMoveDuration, Piece);
		TryPullPieceOfTopTile(Tile);
	}
	else
	{
		Tile->AttachPiece(Piece);
		const auto AnyMatchFound = TryIdentifyAndExecuteMatch(Tile);
		if (!AnyMatchFound)
		{
			Piece->TriggerBounce();
		}
	}
}

void ABoardFlowManager::GenerateNewPieceFromPeak(ATile* PeakTile)
{
	const auto NewPiece = BasicMatch3ToolProvider->PieceGenerator->GenerateRandom(FVector::ZeroVector, FRotator::ZeroRotator);
	const auto TargetTilePosition = PeakTile->GetActorLocation();
	const auto InstantiationPosition = TargetTilePosition + FVector::UpVector * 600;
	NewPiece->SetLocation(InstantiationPosition);
	NewPiece->TriggerFadeIn();
	MovePiece(nullptr, PeakTile, GameplayConstants::PieceMoveDuration, NewPiece);
}


void ABoardFlowManager::MovePiece(ATile* StartTile, ATile* EndTile, const float Duration, APiece* Piece)
{
	const auto StartPosition = StartTile == nullptr ? Piece->GetActorLocation() : StartTile->GetActorLocation();
	if (StartTile != nullptr)
	{
		StartTile->IsTargetedByMovingPiece = false;
	}
	EndTile->IsTargetedByMovingPiece = true;

	const auto Movement = BasicMatch3ToolProvider->BezierMovementManager->StartMovement(
		StartPosition, EndTile->GetActorLocation(), Duration, Piece);
	Movement->OnComplete.AddLambda([=]
	{
		EndTile->IsTargetedByMovingPiece = false;
		OnPieceMovementCompleted(EndTile, Piece);
	});
}
