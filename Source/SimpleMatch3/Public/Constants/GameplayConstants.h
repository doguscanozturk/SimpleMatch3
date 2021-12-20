#pragma once

class GameplayConstants
{
public:
	static constexpr float LengthOfAFrame60 = 0.01666f;
	static constexpr float PieceMoveDuration = LengthOfAFrame60 * 6;
	static constexpr float PieceSwapDuration = LengthOfAFrame60 * 6;
	static constexpr float UnderstandabilityDelayAfterSwap = LengthOfAFrame60 * 5;
	static constexpr float DelayBeforePullingUpperTile = LengthOfAFrame60 * 2;
	static constexpr float DelayBeforeTriggeringTilesEmpty = LengthOfAFrame60 * 10;
};
