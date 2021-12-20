#pragma once
#include "PieceType.h"

namespace PieceHelpers
{
	inline EPieceType GetRandomPieceType(EPieceType Except = EPieceType::None)
	{
		EPieceType RandomPieceType;

		do
		{
			constexpr uint8 IndexOfLastType = static_cast<uint8>(EPieceType::Yellow);
			RandomPieceType = static_cast<EPieceType>(rand() % (IndexOfLastType + 1));
		}
		while (RandomPieceType == Except || RandomPieceType == EPieceType::None);

		return RandomPieceType;
	}
};
