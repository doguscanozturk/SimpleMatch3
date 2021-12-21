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
	TileGrid = tileGrid;
	BasicMatch3ToolProvider = basicMatch3ToolProvider;
	gridController->OnSwipeApproved.AddUObject(this, &ABoardFlowManager::TrySwapTiles);
}

void ABoardFlowManager::Clear()
{
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
			FTimerHandle ThisHandle;
			GetGameInstance()->GetTimerManager().SetTimer(ThisHandle, FTimerDelegate::CreateLambda([this, TileA, TileB]
			{
				const auto AHasMatch = CheckMatch(TileA);
				const auto BHasMatch = CheckMatch(TileB);

				if (!AHasMatch && !BHasMatch)
				{
					SwapTiles(TileB, TileA, false);
				}
			}), GameplayConstants::UnderstandabilityDelayAfterSwap, false);
		});
	}
}

bool ABoardFlowManager::CheckMatch(ATile* CheckTile) const
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
				GetGameInstance()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([=]
				{
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
			}

			return true;
		}

		return false;
	}

	return false;
}


void ABoardFlowManager::OnTileIsEmpty(ATile* Tile) const
{
	if (Tile->IsTargetedByMovingPiece && Tile->AttachedPiece != nullptr)
	{
		return;
	}

	const auto TopTile = TileGrid->GetNeighborTile(Tile, ESwipeDirection::Up);
	if (TopTile != nullptr && TopTile->AttachedPiece != nullptr && TopTile->AttachedPiece->IsAvailableToPullDown())
	{
		const auto TopPiece = TopTile->DetachPiece();

		MovePiece(TopTile, Tile, GameplayConstants::PieceMoveDuration, TopPiece);

		FTimerHandle ThisHandle;
		GetGameInstance()->GetTimerManager().SetTimer(ThisHandle, FTimerDelegate::CreateLambda([=]
		{
			OnTileIsEmpty(TopTile);
		}), GameplayConstants::DelayBeforePullingUpperTile, false);
	}

	if (Tile->I == 0)
	{
		FTimerHandle ThisHandle;
		GetGameInstance()->GetTimerManager().SetTimer(ThisHandle, FTimerDelegate::CreateLambda([=]
		{
			if (!Tile->IsTargetedByMovingPiece)
			{
				GenerateNewPieceFromPeak(Tile);
			}
		}), GameplayConstants::DelayBeforePullingUpperTile, false);
	}
}

void ABoardFlowManager::OnTilesAreEmpty(vector<ATile*> Tiles) const
{
	for (const auto Tile : Tiles)
	{
		OnTileIsEmpty(Tile);
	}
}

void ABoardFlowManager::OnPieceMovementCompleted(ATile* Tile, APiece* Piece) const
{
	const auto BottomTile = TileGrid->GetNeighborTile(Tile, ESwipeDirection::Down);
	if (BottomTile != nullptr && !BottomTile->IsTargetedByMovingPiece && BottomTile->AttachedPiece == nullptr)
	{
		MovePiece(Tile, BottomTile, GameplayConstants::PieceMoveDuration, Piece);
		OnTileIsEmpty(Tile);
	}
	else
	{
		Tile->AttachPiece(Piece);
		const auto AnyMatchFound = CheckMatch(Tile);
		if (!AnyMatchFound)
		{
			Piece->TriggerBounce();
		}
	}
}

void ABoardFlowManager::GenerateNewPieceFromPeak(ATile* PeakTile) const
{
	const auto NewPiece = BasicMatch3ToolProvider->PieceGenerator->GenerateRandom(FVector::ZeroVector, FRotator::ZeroRotator);
	const auto TargetTilePosition = PeakTile->GetActorLocation();
	const auto InstantiationPosition = TargetTilePosition + FVector::UpVector * 600;
	NewPiece->SetLocation(InstantiationPosition);
	NewPiece->TriggerFadeIn();
	MovePiece(nullptr, PeakTile, GameplayConstants::PieceMoveDuration, NewPiece);
}


void ABoardFlowManager::MovePiece(ATile* StartTile, ATile* EndTile, const float Duration, APiece* Piece) const
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
