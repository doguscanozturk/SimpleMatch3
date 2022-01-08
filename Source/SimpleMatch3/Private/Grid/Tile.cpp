#include "Grid/Tile.h"

ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATile::Clear()
{
	const auto Piece = DetachPiece();
	if (Piece != nullptr)
	{
		Piece->Destroy();
	}
}

void ATile::AttachPiece(APiece* Piece, const bool ShouldUpdatePositionInstantly)
{
	if (Piece == nullptr)
	{
		throw new std::exception("Can't attach null piece!");
	}
	
	this->AttachedPiece = Piece;

	Piece->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	if (ShouldUpdatePositionInstantly)
	{
		Piece->SetLocation(GetActorLocation());
	}
	Piece->SetParentIndex(I, J);
}

APiece* ATile::DetachPiece()
{
	if (AttachedPiece == nullptr)
	{
		return nullptr;
	}

	const auto DetachedPiece = AttachedPiece;
	DetachedPiece->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	DetachedPiece->SetParentIndex(-1, -1);
	AttachedPiece = nullptr;
	return DetachedPiece;
}
