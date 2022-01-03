#include "Match/Match.h"

#include "Match/Exceptions/NoMatchFoundException.h"
#include "ThirdParty/boolinq.h"

void UMatch::Initialize()
{
	throw std::exception("Base UMatch class shouldn't be used!");
}

int UMatch::GetMinPieceRequirement()
{
	throw std::exception("Base UMatch class shouldn't be used!");
}

FMatchMatrix UMatch::GetChoreography()
{
	throw std::exception("Base UMatch class shouldn't be used!");
}

void UMatch::InitializeChoreography(FMatchMatrix Choreography)
{
	MatrixChoreographies.Add(Choreography);
}

FMatchIdentity UMatch::CheckShape(const std::vector<APiece*> MatchingPieces)
{
	if (MatchingPieces.size() < GetMinPieceRequirement())
	{
		throw NoMatchFoundException();
	}

	bool IsChoreographyValid = true;

	for (int ChoreographyIndex = 0; ChoreographyIndex < MatrixChoreographies.Num(); ++ChoreographyIndex)
	{
		FMatchMatrix* Choreography = &MatrixChoreographies[ChoreographyIndex];

		for (int i = 0; i < MatchingPieces.size(); ++i)
		{
			IsChoreographyValid = true;
			ValidPiecesCache.clear();

			FIntPoint StartingPieceIndex(MatchingPieces[i]->ParentI, MatchingPieces[i]->ParentJ);
			const auto IndexOffset = Choreography->GetStartIndexOffset();
			StartingPieceIndex.X += IndexOffset.X;
			StartingPieceIndex.Y += IndexOffset.Y;

			//Starts checking from top left element to bottom right.
			for (int RowIndex = 0; RowIndex < Choreography->Rows.Num(); ++RowIndex)
			{
				const FMatchMatrixRow* Row = &Choreography->Rows[RowIndex];
				for (int ColumnIndex = 0; ColumnIndex < Row->Elements.Num(); ++ColumnIndex)
				{
					const uint8 ChoreographyElement = Row->Elements[ColumnIndex];
					if (ChoreographyElement == 1)
					{
						const FIntPoint WantedIndex(StartingPieceIndex.X + RowIndex, StartingPieceIndex.Y + ColumnIndex);
						const bool HasWantedPiece = boolinq::from(MatchingPieces).any([WantedIndex](const APiece* Piece)
						{
							const bool IsValid = Piece->ParentI == WantedIndex.X && Piece->ParentJ == WantedIndex.Y;
							return IsValid;
						});

						if (!HasWantedPiece)
						{
							IsChoreographyValid = false;
							break;
						}

						auto WantedPiece = boolinq::from(MatchingPieces).first([WantedIndex](const APiece* Piece)
						{
							return Piece->ParentI == WantedIndex.X && Piece->ParentJ == WantedIndex.Y;
						});
						ValidPiecesCache.push_back(WantedPiece);
					}
				}

				if (!IsChoreographyValid)
				{
					break;
				}
			}

			if (IsChoreographyValid)
			{
				break;
			}
		}

		if (IsChoreographyValid)
		{
			FMatchIdentity Identity;
			Identity.Pieces.Append(&ValidPiecesCache[0], ValidPiecesCache.size());
			return Identity;
		}
	}

	throw NoMatchFoundException();
}
