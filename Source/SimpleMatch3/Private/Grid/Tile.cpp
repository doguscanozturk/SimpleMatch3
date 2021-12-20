#include "Grid/Tile.h"

#include "Utility/TestMacros.h"

ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATile::Clear()
{
	const auto Piece = DetachPiece();
	Piece->Destroy();
}

void ATile::AttachPiece(APiece* Piece, const bool ShouldUpdatePositionInstantly)
{
	this->AttachedPiece = Piece;
	if(Piece == nullptr)
	{
		DEBUG("WTF that shit is null [%i][%i]", I, J);
		return;
	}
	
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
		throw std::exception("Can't detach null piece.");
	}

	const auto DetachedPiece = AttachedPiece;
	DetachedPiece->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	DetachedPiece->SetParentIndex(-1, -1);
	AttachedPiece = nullptr;
	return DetachedPiece;
}