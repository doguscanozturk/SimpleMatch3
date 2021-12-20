#pragma once

namespace CameraHelpers
{
	inline void PlaceCameraToTheCenterOfTheGrid(const UTileGrid* TileGrid, AActor* Camera)
	{
		const auto FirstTile = TileGrid->GetTile(0, 0);
		const auto LastTile = TileGrid->GetTile(TileGrid->Width - 1, TileGrid->Height - 1);
		const auto TopLeftMostTileLocation = FirstTile->GetActorLocation();
		const auto BottomRightMostTileLocation = LastTile->GetActorLocation();

		constexpr float CameraDistance = -4000.f;
		const FVector MidPoint = (TopLeftMostTileLocation + BottomRightMostTileLocation) / 2;
		Camera->SetActorLocation(FVector(MidPoint.X, CameraDistance, MidPoint.Z));
	}
};
