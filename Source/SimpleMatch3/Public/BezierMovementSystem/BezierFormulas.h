#pragma once

namespace BezierFormulas
{
	static FVector Linear(const FVector Start, const FVector End, const float T)
    {
        return FMath::Lerp(Start, End, T);
    }

	static FVector Quadratic(const FVector Start, const FVector End, const FVector C1, const float T)
	{
		const float OneMinusT = 1.0f - T;
		return OneMinusT * OneMinusT * Start +
			   2.f * OneMinusT * T * C1 +
			   T * T * End;
	}

	static FVector Cubic(const FVector Start, const FVector End, const FVector C1, const FVector C2, const float T)
	{
		const float OneMinusT = 1.f - T;
		return OneMinusT * OneMinusT * OneMinusT * Start +
			   3.f * OneMinusT * OneMinusT * T * C1 +
			   3.f * OneMinusT * T * T * C2 +
			   T * T * T * End;
	}

	static FVector GetFirstDerivative(const FVector Start, const FVector End, const FVector C1, const float T)
	{
		return 2.f * (1.f - T) * (C1 - Start) +
			   2.f * T * (End - C1);
	}

	static FVector GetFirstDerivative(const FVector Start, const FVector End, const FVector C1, const FVector C2, float T)
	{
		T = FMath::Clamp(T, 0.f, 1.f);
		const float OneMinusT = 1.f - T;
		return 3.f * OneMinusT * OneMinusT * (C1 - Start) +
			   6.f * OneMinusT * T * (C2 - C1) +
			   3.f * T * T * (End - C2);
	}
};
